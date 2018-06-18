import nltk
from nltk.tokenize import TweetTokenizer

def analyze(text, negative, positive):
    """Analyze text for sentiment, returning its score."""

    tokenizer = TweetTokenizer()
    tweetWords = tokenizer.tokenize(text)

    score = 0
    counted = 0
    t = 0

    for t in range(len(tweetWords) - 1):
        for neg in range(4782):
            if str.lower(tweetWords[t]) == negative[neg]:
                score = score - 1
                counted = 1

        for pos in range(2006):
            if counted != 1:
                if str.lower(tweetWords[t]) == positive[pos]:
                    score = score + 1

        else:
            counted = 0

    return score