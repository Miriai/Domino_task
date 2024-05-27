#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>

//--------------------------------------------------------------------------------------------------

// Helper function to check if the front or back of seq1 matches the front or back of seq2
template<typename T>
bool has_matching_ends(const std::vector<T>& seq1, const std::vector<T>& seq2) {
    if (seq1.empty() || seq2.empty()) {
        throw std::invalid_argument("One of the sequences is empty");
    }
    return (seq1.front() == seq2.front()) ||
        (seq1.front() == seq2.back()) ||
        (seq1.back() == seq2.front()) ||
        (seq1.back() == seq2.back());
}

//--------------------------------------------------------------------------------------------------

// Helper function to check if the front or back of seq1 matches the common letter
template<typename T>
bool has_common_end(const std::vector<T>& seq, const T end) {
    if (seq.empty()) {
        throw std::invalid_argument("The sequence is empty");
    }
    return (seq.front() == end || seq.back() == end);
}

//--------------------------------------------------------------------------------------------------

template<typename T>
T find_common_end(const std::vector<T>& seq1, const std::vector<T>& seq2) {
    if (seq1.empty() || seq2.empty()) {
        throw std::invalid_argument("One of the sequences is empty");
    }
    // Check if the front or back of seq1 matches the front or back of seq2
    if (seq1.front() == seq2.front() || seq1.front() == seq2.back()) {
        return seq1.front();  // Return the common front element
    }
    else if (seq1.back() == seq2.front() || seq1.back() == seq2.back()) {
        return seq1.back();   // Return the common back element
    }
    else {
        throw std::runtime_error("No common end found");
    }
}

//--------------------------------------------------------------------------------------------------

// Function to check if two sequences can be merged
template<typename T>
bool can_merge(const std::vector<T>& seq1, const std::vector<T>& seq2,
    const std::vector<std::vector<T>>& sequences) {
    // Check if seq1 and seq2 have matching ends
    if (has_matching_ends(seq1, seq2)) {
        T common = find_common_end(seq1, seq2);
        // Check if the matching ends are not shared by any other sequence
        for (const auto& seq : sequences) {
            if (&seq != &seq1 && &seq != &seq2) {
                // Check if it's not the two sequences that need to be merged
                if (has_common_end(seq, common) || has_common_end(seq, common)) {
                    // Check that there are more sequences with the same ends
                    return false; // Matching end found in another sequence
                }
            }
        }
        return true; // Can merge
    }
    return false; // No matching ends found
}

//--------------------------------------------------------------------------------------------------

// Function to merge two sequences
template<typename T>
std::vector<T> merge_sequences_by_order(const std::vector<T>& seq1, const std::vector<T>& seq2) {
    std::vector<T> mergedSeq;
    mergedSeq.insert(mergedSeq.end(), seq1.begin(), seq1.end()); // Insert the first
    mergedSeq.insert(mergedSeq.end(), seq2.begin() + 1, seq2.end());
    // Insert the second without the common letter

    return mergedSeq;
}

//--------------------------------------------------------------------------------------------------

// Function to merge two sequences
template<typename T>
std::vector<T> merge_sequences(const std::vector<T>& seq1, const std::vector<T>& seq2) {
    if (seq1.empty() || seq2.empty()) {
        throw std::invalid_argument("One of the sequences is empty");
    }
    std::vector<T> mergedSeq;
    auto it1 = seq1;
    auto it2 = seq2;
    if (seq1.front() == seq2.front()) { // If the common character at the beginning of both sequences 
        std::reverse(it1.begin(), it1.end());
        mergedSeq = merge_sequences_by_order(it1, seq2);
    }
    else if (seq1.front() == seq2.back()) {
        // If the common character is at the beginning of the first sequence and at the end of the second
        mergedSeq = merge_sequences_by_order(seq2, seq1);
    }
    else if (seq1.back() == seq2.front()) {
        //If the common character is at the end of the first sequence and the beginning of the second
        mergedSeq = merge_sequences_by_order(seq1, seq2);
    }
    else if (seq1.back() == seq2.back()) {
        // If the common character at the end of both sequences
        std::reverse(it2.begin(), it2.end());
        mergedSeq = merge_sequences_by_order(seq1, it2);
    }

    return mergedSeq;
}

//--------------------------------------------------------------------------------------------------

// Function to merge pairs of sequences until no more merges are possible
template<typename T>
void merge_pairs_only(std::vector<std::vector<T>>& sequences) {
    bool merged = true;
    while (merged) {
        merged = false;
        for (auto it1 = sequences.begin(); it1 != sequences.end(); ++it1) {
            for (auto it2 = it1 + 1; it2 != sequences.end(); ++it2) {
                if (can_merge(*it1, *it2, sequences)) { //Check if the two sequences can merge
                    *it1 = merge_sequences(*it1, *it2);
                    sequences.erase(it2); // Erase the sequence who has already merged
                    merged = true;
                    break;
                }
            }
            if (merged) {
                break;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

// Function to print a vector of vectors
template<typename T>
void print_vector(const std::vector<std::vector<T>>& sequences) {
    for (const auto& seq : sequences) {
        for (const auto& element : seq) {
            std::cout << element;
        }
        std::cout << " ";
    }
}

//--------------------------------------------------------------------------------------------------

int main() {
    try {
        std::vector<std::vector<char>> sequences;

        // Prompt the user to enter sequences
        std::cout << "Enter sequences, separating elements with 'Enter'. Enter an empty line to finish:\n";

        std::string input;
        while (std::getline(std::cin, input) && !input.empty()) {
            std::istringstream iss(input);
            std::vector<char> seq;
            char element;
            while (iss >> element) {
                seq.push_back(element);
            }
            sequences.push_back(seq);
        }

        // Merge the sequences
        merge_pairs_only(sequences);

        // Print the merged sequences
        std::cout << "Merged sequences: ";
        print_vector(sequences);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
