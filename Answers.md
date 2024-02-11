# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name: Razkia Rouabah

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## UML Diagram

Add your UML class diagram here.

Replace the following image with your diagram. You can draw it by hand and take a photo.
![UML Class Diagram](UML_class.png)

## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

> To train the model, the Classifier::train method is called which opens the training data file, reads each tweet line by line, cleans and tokenizes the tweet text, and updates the word sentiment counts in a map.

To classify a new tweet, the Classifier::classify method takes the tokenized words of the tweet, looks up the sentiment score for each word in the map, and sums the scores to determine an overall positive or negative classification.

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the comple

>  The training takes O(NHM*logK) time, where:

N is the number of tweets
H is the average number of words per tweet
M is the average number of characters per word
K is the number of unique words across all tweets

It takes this time because reading and tokenizing all the tweets is O(NHM) and looking up the sentiment for each of the O(NHM) words takes O(logK) time. The map lookups dominate the complexity.

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > Classifying a single tweet takes O(W) time where W is the number of words in the tweet. This is because it loops through each word to lookup and sum the sentiment scores.

4. How do you know that you use proper memory management? I.e., how do you know that you do not have
   a memory leak?

   > Memory is properly managed using RAII techniques - resource allocation is initialization. The string classes like DSString automatically handle allocation/deallocation. Vectors and maps also manage their own memory. No manual memory management is needed so there are no leaks.

5. What was the most challenging part of the assignment?

   > The most challenging part was robustly handling all the string processing like tokenizing, lowercase, removing punctuation, etc. Having good string utility functions was important for this.