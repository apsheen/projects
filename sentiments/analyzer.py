import nltk
from nltk.tokenize import TweetTokenizer

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self):
        """Initialize Analyzer."""

        negPath = 'negative-words.txt'
        posPath = 'positive-words.txt'

        negWords = open(negPath,'r')
        posWords = open(posPath,'r')

        self.negative = negWords.readlines()
        self.positive = posWords.readlines()

        print(self.negative)
        print(self.positive)
        print("work")

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        tokenizer = TweetTokenizer()
        tweetWords = tokenizer.tokenize(text)

        score = 0
        counted = 0

        #get rid of the "/n"
        for n in range(4783):
            convertneg = ""
            convertneg = self.negative[n]
            convertneg = convertneg[:-1]
            self.negative[n] = convertneg

        for p in range(4784):
            convertpos = ""
            convertpos = self.positive[p]
            convertpos = convertpos[:-1]
            self.positive[n] = convertpos

        for t in range(len(text)):
           for neg in range(4783):
              if str.lower(tweetWords[t]) == self.negative[neg]:
                  score = score - 1
                  counted = 1

           for pos in range(2007):
              if counted != 1:
                  if str.lower(tweetWords[t]) == self.positive[pos]:
                      score = score + 1

              else:
                  counted = 0

        return score
