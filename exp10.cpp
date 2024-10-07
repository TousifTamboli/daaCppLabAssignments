#include <iostream>
#include <string>
using namespace std;

// Function to implement Rabin-Karp algorithm
void searchRabinKarp(string pattern, string text) {
    int prime = 101; // A prime number to modulate hash values
    int patternLength = pattern.length();
    int textLength = text.length();
    int patternHash = 0; // Hash value for pattern
    int textHash = 0; // Hash value for current window of text
    int h = 1;

    // Calculate h = (prime^(patternLength-1)) % prime
    for (int i = 0; i < patternLength - 1; i++) {
        h = (h * prime) % prime;
    }

    // Calculate hash value of pattern and the initial window of text
    for (int i = 0; i < patternLength; i++) {
        patternHash = (prime * patternHash + pattern[i]) % prime;
        textHash = (prime * textHash + text[i]) % prime;
    }

    // Slide the pattern over text one by one
    for (int i = 0; i <= textLength - patternLength; i++) {
        // Check hash values of current window of text and pattern
        if (patternHash == textHash) {
            // If hash values match, then check character by character
            bool match = true;
            for (int j = 0; j < patternLength; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        // Calculate hash value for next window of text
        if (i < textLength - patternLength) {
            textHash = (prime * (textHash - text[i] * h) + text[i + patternLength]) % prime;
            if (textHash < 0) {
                textHash = (textHash + prime) % prime;
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    cout << "Occurrences:" << endl;
    searchRabinKarp(pattern, text);
    return 0;
}
