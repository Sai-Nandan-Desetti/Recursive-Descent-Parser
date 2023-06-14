# Recursive-Descent-Parser
A recursive descent parser in C.

The implementation is based on the pseudocode presented in *System Software - An Introduction to Systems Programming* by Leland Beck.

### What is a recursive descent parser?
A recursive-descent parser is made up of a procedure for each nonterminal symbol in the grammar. 
When a procedure is called, it attempts to find a substring of the input, beginning with the current token, that can be interpreted as the nonterminal with which the procedure is associated.
In the process of doing this, it may call other procedures, or even call itself recursively, to search for other nonterminals.
If a procedure finds the nonterminal that is its goal, it returns an indication of success to its caller. 
It also advances the current-token pointer past the substring it has just recognized.
If the procedure is unable to find a substring that can be interpreted as the desired nonterminal, it returns an indication of failure, or invokes an error diagnosis and recovery routine.

### For what grammar is this parser written?
The parser is written for the grammar shown in Fig: 5.15, using the coding scheme in Fig: 5.5.

![Simplified Pascal Grammar](https://github.com/Sai-Nandan-Desetti/Recursive-Descent-Parser/assets/80631906/03754885-885f-422d-a1ab-a505a6688290)
![Token coding scheme](https://github.com/Sai-Nandan-Desetti/Recursive-Descent-Parser/assets/80631906/4c5b26ca-9014-4044-9828-164bde683ede)

(Pictures are taken from the aforementioned book.)

### Details
* The parser is written only for the following rules: 6a, 9, 10a, 11a, 12, and 13.
* Thus, the input statement should only be based on these rules.
* The input should be in all CAPS.
* Do not add a semi-colon at the end.

### Example
```
Enter a statement: SUM := A + B

READ:   false

IDLIST: false

ASSIGN: true

EXP:    false

TERM:   false

FACTOR: false
```
The program returns `true` for `ASSIGN` because we've input an assignment.
