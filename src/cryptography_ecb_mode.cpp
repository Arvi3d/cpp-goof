// Summary: Incorrect Cryptographic Usage - Using ECB Mode
// Electronic Codebook (ECB) mode is a block cipher mode of operation that is
// insecure for most purposes. In ECB mode, each block of plaintext is encrypted
// independently with the same key. This means that identical plaintext blocks
// will always produce identical ciphertext blocks. This property leaks
// information about the plaintext's structure. For example, in an image
// encrypted with ECB, patterns from the original image often remain visible.
// ECB mode does not use an Initialization Vector (IV) and is not recommended
// for encrypting more than one block of data with the same key.

#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For std::hex, std::setw, std::setfill
#include <openssl/evp.h>
#include <openssl/err.h> // For error handling
#include <algorithm> // For std::equal

// Hardcoded Key (bad practice, but focus is on ECB mode here)
const unsigned char key[16] = { // AES-128 key
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
};

void print_hex_ecb(const std::string& label, const unsigned char* data, int len) {
    std::cout << label << ": ";
    for (int i = 0; i < len; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
        if ((i + 1) % 16 == 0 && (i + 1) < len) std::cout << " "; // Add space between blocks for readability
    }
    std::cout << std::dec << std::endl;
}

// Encrypts using AES-128-ECB
std::vector<unsigned char> encrypt_with_ecb_mode(const std::vector<unsigned char>& plaintext) {
    std::vector<unsigned char> ciphertext_buffer;
    EVP_CIPHER_CTX *ctx = nullptr;
    int len = 0;
    int ciphertext_len = 0;

    if (plaintext.empty() || plaintext.size() % 16 != 0) {
        std::cerr << "Error: Plaintext for ECB mode must be non-empty and a multiple of the block size (16 bytes for AES)." << std::endl;
        return ciphertext_buffer;
    }

    if(!(ctx = EVP_CIPHER_CTX_new())) {
        std::cerr << "Error: EVP_CIPHER_CTX_new failed." << std::endl; ERR_print_errors_fp(stderr);
        return ciphertext_buffer;
    }

    // Initialise the encryption operation with AES-128-ECB.
    // No IV is used for ECB mode.
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, key, nullptr)) {
        std::cerr << "Error: EVP_EncryptInit_ex failed." << std::endl; ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        return ciphertext_buffer;
    }
    
    EVP_CIPHER_CTX_set_padding(ctx, 0); // Disable padding for this demo

    ciphertext_buffer.resize(plaintext.size()); // ECB ciphertext is same size as plaintext (if no padding)
    if(1 != EVP_EncryptUpdate(ctx, ciphertext_buffer.data(), &len, plaintext.data(), plaintext.size())) {
        std::cerr << "Error: EVP_EncryptUpdate failed." << std::endl; ERR_print_errors_fp(stderr);
        EVP_CIPHER_CTX_free(ctx);
        ciphertext_buffer.clear();
        return ciphertext_buffer;
    }
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext_buffer.data() + len, &len)) {
        std::cerr << "Error: EVP_EncryptFinal_ex failed." << std::endl; ERR_print_errors_fp(stderr);
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
    std::vector<unsigned char> plaintext_pattern(32);
    for(int i=0; i < 16; ++i) plaintext_pattern[i] = 'A'; 
    for(int i=16; i < 32; ++i) plaintext_pattern[i] = 'A'; 

    std::vector<unsigned char> plaintext_varied(32);
    for(int i=0; i < 16; ++i) plaintext_varied[i] = 'B'; 
    for(int i=16; i < 32; ++i) plaintext_varied[i] = 'C'; 

    std::cout << "Encrypting with ECB mode (AES-128-ECB):" << std::endl;
    print_hex_ecb("Key              ", key, sizeof(key));
    
    print_hex_ecb("Plaintext Pattern", plaintext_pattern.data(), plaintext_pattern.size());
    std::vector<unsigned char> ciphertext_pattern = encrypt_with_ecb_mode(plaintext_pattern);
    if (!ciphertext_pattern.empty()) {
        print_hex_ecb("Ciphertext Pattern", ciphertext_pattern.data(), ciphertext_pattern.size());
        if (ciphertext_pattern.size() == 32 && 
            std::equal(ciphertext_pattern.begin(), ciphertext_pattern.begin() + 16, ciphertext_pattern.begin() + 16)) {
            std::cout << "\nVULNERABILITY CONFIRMED: Identical plaintext blocks resulted in identical ciphertext blocks." << std::endl;
        }
    }

    print_hex_ecb("Plaintext Varied ", plaintext_varied.data(), plaintext_varied.size());
    std::vector<unsigned char> ciphertext_varied = encrypt_with_ecb_mode(plaintext_varied);
     if (!ciphertext_varied.empty()) {
        print_hex_ecb("Ciphertext Varied ", ciphertext_varied.data(), ciphertext_varied.size());
    }

    return 0;
}

// Mitigation Strategy:
// To avoid the weaknesses of ECB mode:
// 1. Do Not Use ECB Mode: For nearly all applications, ECB mode should be avoided.
// 2. Use Secure Cipher Modes: Employ modes of operation that provide semantic
//    security, such as:
//    - CBC (Cipher Block Chaining): Requires a unique, unpredictable IV for each
//      encryption with the same key.
//    - CTR (Counter Mode): Requires a unique nonce (number used once) for each
//      encryption with the same key. Often combined with a counter.
//    - GCM (Galois/Counter Mode): An Authenticated Encryption with Associated
//      Data (AEAD) mode. Provides both confidentiality and integrity. Requires
//      a unique nonce for each encryption with the same key. Reusing a (key, nonce)
//      pair in GCM is catastrophic.
//    - CCM (Counter with CBC-MAC): Another AEAD mode.
// 3. Always Use a Proper IV/Nonce: For modes that require an IV or nonce, ensure
//    it is generated correctly (unique, often random/unpredictable) for each
//    encryption operation under the same key.
// 4. Prefer Authenticated Encryption (AEAD): Modes like GCM or CCM are generally
//    preferred as they provide both confidentiality and integrity/authentication,
//    protecting against a wider range of attacks.
