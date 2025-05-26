// Summary: Incorrect Cryptographic Usage - Hardcoded IV
// Using a hardcoded Initialization Vector (IV) with block cipher modes like
// CBC (Cipher Block Chaining) is a serious security vulnerability. An IV is
// meant to introduce randomness to the encryption process, ensuring that
// encrypting the same plaintext multiple times with the same key produces
// different ciphertexts. If the IV is hardcoded and thus reused, identical
// plaintexts will produce identical ciphertexts, leaking information.
// Furthermore, for some modes, a predictable IV can lead to chosen-plaintext
// attacks or other cryptographic weaknesses. IVs should be unique and
// unpredictable (ideally random) for each encryption operation with the same key.

#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For std::hex, std::setw, std::setfill
#include <openssl/evp.h>
#include <openssl/rand.h> // For generating a proper IV in mitigation

// Hardcoded Key (also bad practice, but focus is on IV here)
const unsigned char key[16] = { // AES-128 key
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

// !!! VULNERABILITY: Hardcoded IV !!!
const unsigned char hardcoded_iv[16] = { // AES block size is 16 bytes
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
};

void print_hex(const std::string& label, const unsigned char* data, int len) {
    std::cout << label << ": ";
    for (int i = 0; i < len; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    std::cout << std::dec << std::endl;
}

// Encrypts using AES-128-CBC with a hardcoded IV
std::vector<unsigned char> encrypt_with_hardcoded_iv(const std::string& plaintext) {
    std::vector<unsigned char> ciphertext_buffer;
    EVP_CIPHER_CTX *ctx = nullptr;
    int len = 0;
    int ciphertext_len = 0;

    // Create and initialise the context
    if(!(ctx = EVP_CIPHER_CTX_new())) {
        std::cerr << "Error: EVP_CIPHER_CTX_new failed." << std::endl;
        return ciphertext_buffer;
    }

    // Initialise the encryption operation with AES-128-CBC.
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key, hardcoded_iv)) {
        std::cerr << "Error: EVP_EncryptInit_ex failed." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return ciphertext_buffer;
    }

    // Provide the message to be encrypted, and obtain the encrypted output.
    // EVP_EncryptUpdate can be called multiple times if necessary.
    // Ciphertext can be EVP_MAX_BLOCK_LENGTH (16 for AES) bytes longer than plaintext.
    ciphertext_buffer.resize(plaintext.length() + EVP_CIPHER_block_size(EVP_aes_128_cbc()));
    if(1 != EVP_EncryptUpdate(ctx, ciphertext_buffer.data(), &len, 
                             reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length())) {
        std::cerr << "Error: EVP_EncryptUpdate failed." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        ciphertext_buffer.clear();
        return ciphertext_buffer;
    }
    ciphertext_len = len;

    // Finalise the encryption. Further ciphertext bytes may be written at this stage.
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext_buffer.data() + len, &len)) {
        std::cerr << "Error: EVP_EncryptFinal_ex failed." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        ciphertext_buffer.clear();
        return ciphertext_buffer;
    }
    ciphertext_len += len;
    ciphertext_buffer.resize(ciphertext_len);

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_buffer;
}

int main() {
    std::string plaintext1 = "This is a secret message.";
    std::string plaintext2 = "This is a secret message."; // Same plaintext
    std::string plaintext3 = "This is a different message.";

    std::cout << "Encrypting with hardcoded IV (AES-128-CBC):" << std::endl;
    print_hex("Key         ", key, sizeof(key));
    print_hex("Hardcoded IV", hardcoded_iv, sizeof(hardcoded_iv));
    
    std::vector<unsigned char> ciphertext1 = encrypt_with_hardcoded_iv(plaintext1);
    std::vector<unsigned char> ciphertext2 = encrypt_with_hardcoded_iv(plaintext2); // Should use the same hardcoded IV
    std::vector<unsigned char> ciphertext3 = encrypt_with_hardcoded_iv(plaintext3);

    if (!ciphertext1.empty()) print_hex("Ciphertext 1 (PT1)", ciphertext1.data(), ciphertext1.size());
    if (!ciphertext2.empty()) print_hex("Ciphertext 2 (PT1)", ciphertext2.data(), ciphertext2.size()); 
    if (!ciphertext3.empty()) print_hex("Ciphertext 3 (PT3)", ciphertext3.data(), ciphertext3.size());

    if (!ciphertext1.empty() && !ciphertext2.empty() && ciphertext1 == ciphertext2) {
        std::cout << "\nVULNERABILITY CONFIRMED: Identical plaintexts encrypted with the same key and hardcoded IV produce identical ciphertexts." << std::endl;
    } else if (ciphertext1.empty() || ciphertext2.empty()){
        std::cout << "\nEncryption failed for one or both plaintexts, cannot confirm vulnerability status via comparison." << std::endl;
    } else if (ciphertext1 != ciphertext2) {
         std::cout << "\nUNEXPECTED: Ciphertexts for identical plaintexts are different despite hardcoded IV. Check encryption logic." << std::endl;
    }


    return 0;
}

// Mitigation Strategy:
// To prevent issues with hardcoded IVs:
// 1. Generate a Unique, Unpredictable IV for Each Encryption: For modes like
//    CBC and CTR, the IV must be unique and unpredictable for each message
//    encrypted with the same key. Typically, a cryptographically secure
//    random number generator (CSRNG) is used.
//    Example (using OpenSSL's RAND_bytes):
//    unsigned char random_iv[16]; // For AES, IV size is usually block size (16 bytes)
//    if (1 != RAND_bytes(random_iv, sizeof(random_iv))) {
//        // Handle error: RNG failure
//    }
//    // Use random_iv in EVP_EncryptInit_ex
// 2. Prepend IV to Ciphertext: The IV does not need to be secret, but it must
//    be available for decryption. A common practice is to prepend the (randomly
//    generated) IV to the ciphertext. The decryptor then reads the IV from the
//    beginning of the received data before decrypting the rest.
// 3. Never Reuse IVs with the Same Key: This is the fundamental rule for modes like CBC.
// 4. Understand IV Requirements for Chosen Cipher Mode: Different cipher modes
//    (e.g., GCM, CTR, CBC, OFB) have different requirements for their IVs/nonces.
//    For GCM and CTR, uniqueness is paramount; predictability is less of an issue
//    than for CBC, but still, random IVs are good practice. Reusing a (key, IV)
//    pair in GCM is catastrophic.
// 5. Use Authenticated Encryption (AEAD) Modes: Modes like AES-GCM provide both
//    encryption and authentication. They still require a unique nonce (similar to an IV).
