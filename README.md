# Levelic Tree Cipher - LTC

---

## Introduction

The Levelic Tree Cipher is a cryptographic algorithm that encodes and decodes plaintext using a perfect tree structure.

The tree is constructed based on a **specified number of children per node**, and the plaintext is padded to fit the
tree
structure. The encryption process involves building the tree and creating an adjacency list representation, while
decryption involves traversing the tree to retrieve the original plaintext.

So basically this Cipher key = **number of children per node**

---

## Code Structure

* Encryption: The plaintext is encoded using the `levelicTreeEncryptor` function, which constructs the tree and generates
  the ciphertext.
* Decryption: The ciphertext is decoded using the `levelicTreeDecryptor` function, which reconstructs the plaintext from
  the output of the DFS result.

---

## Usage

1. **Compile**:
    * Compile the code using any C++ compiler, it's recommended to use C++17.

2. **Encryption**:
    * Specify the number of children per node (nodeChildrenCtr).
    * Provide the plaintext to be encrypted (plainText).
    * Call the levelicTreeEncryptor function to generate the ciphertext.
    *
3. **Decryption**:
    * Use the same number of children per node as in the encryption process.
    * Provide the ciphertext obtained during encryption.
    * Call the levelicTreeDecryptor function to recover the plaintext.

#### Example:

```c++
// Define the number of children per node
// The tree can be binary, ternary, quadratic or anything else.
int nodeChildrenCtr = 3; // Ternary Tree

// Specify the plaintext
string plainText = "sample text for levelic tree cipher";

// Encrypt the plaintext
string cipherText = levelicTreeEncryptor(nodeChildrenCtr, plainText);

// Decrypt the ciphertext
string recoveredPt = levelicTreeDecryptor(nodeChildrenCtr, cipherText);
```
As the output will be this:
```
[Plain Text]: 			sample text for levelic tree cipher
[Cipher Text]: 			salor elev elimtc tereex ciptphe r$$f$$$

[Recovered Plain Text]: 	sample text for levelic tree cipher
```

---

## Contributors

* **Homam Manasra**

