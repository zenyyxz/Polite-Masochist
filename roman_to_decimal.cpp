#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

/**
 * The "Humanizer" - Roman to Decimal Converter
 * 
 * Okay, look. INTERCAL's Roman numerals are a work of art, but even I have to 
 * admit that reading 'LXVCDLXXIX' when you just want '65479' is a bit much. 
 * Sophie said it was "cute," but my brain is already fried from the COME FROMs.
 * 
 * This little C++ tool takes the mess that INTERCAL (and my logger) spits out 
 * and turns it back into something a normal person can understand. 
 * It handles the weird "overline-as-underscores" logic too.
 */

// A simple map because I'm not doing this bitwise in C++... I'm not THAT masochistic.
int get_roman_value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default:  return 0;
    }
}

// The core logic for standard Roman numerals.
int parse_standard_roman(const std::string& roman) {
    int result = 0;
    int previous = 0;
    
    // We walk backwards because it's easier to handle the subtractive notation (IV, IX, etc.)
    for (int i = roman.length() - 1; i >= 0; --i) {
        int current = get_roman_value(roman[i]);
        if (current < previous) {
            result -= current;
        } else {
            result += current;
        }
        previous = current;
    }
    return result;
}

// Just a helper to clean up the strings.
std::string clean_string(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

int main() {
    std::ifstream raw_primes("primes.txt");
    if (!raw_primes.is_open()) {
        std::cerr << "Wait, where's primes.txt? You gotta run the sieve first!" << std::endl;
        return 1;
    }

    std::ofstream human_primes("primes_in_decimal.txt");
    if (!human_primes.is_open()) {
        std::cerr << "Can't open primes_in_decimal.txt. Permission issues?" << std::endl;
        return 1;
    }

    std::string current_line;
    std::string saved_overline = "";

    while (std::getline(raw_primes, current_line)) {
        // If the line has underscores, it's an "overline" for the NEXT prime number.
        // It tells us how many of the leading characters are in the thousands.
        bool is_overline = (current_line.find('_') != std::string::npos);

        if (is_overline) {
            saved_overline = current_line;
        } else {
            std::string roman = clean_string(current_line);
            if (roman.empty()) continue;

            int final_decimal = 0;

            if (saved_overline.empty()) {
                // Simple case: just a normal Roman numeral.
                final_decimal = parse_standard_roman(roman);
            } else {
                // The tricky case: INTERCAL overlines.
                // Count the underscores to see how many chars are "thousands".
                int underscore_count = 0;
                for (char c : saved_overline) if (c == '_') underscore_count++;

                if (underscore_count > 0 && underscore_count <= (int)roman.length()) {
                    std::string thousands = roman.substr(0, underscore_count);
                    std::string ones = roman.substr(underscore_count);
                    final_decimal = (parse_standard_roman(thousands) * 1000) + parse_standard_roman(ones);
                } else {
                    final_decimal = parse_standard_roman(roman);
                }
                saved_overline = ""; // Reset for the next one.
            }
            human_primes << final_decimal << "\n";
        }
    }

    raw_primes.close();
    human_primes.close();
    
    return 0;
}
