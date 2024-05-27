Miriam Cohen Bitan - Miriamcohenbitan@gmail.com

# Domino Task
The function takes a collection of sequences of an arbitrary type,
and merges pairs of sequences under specific conditions,
until all possible merges have been accomplished.

Run the "Domino_task.cpp" file

To insert sequences- insert each one on a separate line.
To finish, insert a blank line

## Merging conditions:
1. The order of sequences in both input and output collections is irrelevant (`['abc', 'cde']` is equivalent to `['cde', 'abc']`)
2. The sequences can be reversed if needed for merging. E.g.: `'abc'` can be converted to `'cba'` if required (Similarly to the domino game).
3. Merge between two sequences is possible if and only if both of the following conditions hold:  
3.1. The first/last element of one sequence matches the first/last element of the other sequence.  
3.2. The common end element of the two sequences is not present as the first/last element of any other sequences in the collection.  
4. Merging means concatinating two sequences with a common element at their ends, into a longer one with the common element kept only once at the "connection point" of the result sequence.
