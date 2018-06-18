from twython import Twython, TwythonAuthError, TwythonError, TwythonRateLimitError, TwythonStreamer
from nltk import TweetTokenizer
from chart import chart
import timer

def analyze(text):
        """Analyze text for sentiment, returning its score."""
        tokenizer = TweetTokenizer()
        tweetWords = tokenizer.tokenize(text)

        for i in range(len(tweetWords) - 1):
            tweetWords[i] = str.lower(tweetWords[i])

        score = 0
        counted = 0

        #get rid of the "/n"
        for n in range(4783):
            convertneg = ""
            convertneg = negative[n]
            convertneg = convertneg[:-1]
            negative[n] = convertneg

        for p in range(2006):
            convertpos = ""
            convertpos = positive[p]
            convertpos = convertpos[:-1]
            positive[p] = convertpos

        for t in range(len(tweetWords) - 1):
           for neg in range(4783):
              if str.lower(tweetWords[t]) == negative[neg]:
                  score = -1
                  counted = 1

           for pos in range(2006):
              if counted != 1:
                  if str.lower(tweetWords[t]) == positive[pos]:
                      score = score + 1

              else:
                  counted = 0

        return score

API_KEY = 'lCTVJrOC6BmdQjRydTsxjNOpv'
API_SECRET = 'dVLXNMOPziY1YmRblwMZ1yvqqaayZhAPCRvZI6hCY20jMHc5Aw'
OAUTH_TOKEN = '1004873339913977857-s6wBHjEm2BFTByCxxkiHnwOjv52W3A'
OAUTH_TOKEN_SECRET = 'UF4UsXTjKMeZaE9xsCMrFujaxNdAqeGj9NrA6zwEinjmh'

twitter = Twython(API_KEY, API_SECRET, OAUTH_TOKEN, OAUTH_TOKEN_SECRET)

negPath = 'negative-words.txt'
posPath = 'positive-words.txt'

negWords = open(negPath,'r')
posWords = open(posPath,'r')

negative = negWords.readlines()
positive = posWords.readlines()

negmessage = [1, ' Apologies for Trump and his rudeness today. @realDonaldTrump']
posmessage = [1, ' Wow, Donald Trump managed to actually be decent today! @realDonaldTrump']

class MyStreamer(TwythonStreamer):
    def on_success(self, data):
        if 'text' in data:
            score = analyze(data['text'])

            if(score >= 0):
                print(data['text'])
                print(score)

                #if 2 minutes no input, continue with posmessage - change later
                try:
                    answer = timer.input_with_timeout("Is this tweet actually positive/neutral? Y for yes, N for no: ", 10)
                except timer.TimeoutExpired:
                    twitter.update_status(status=posmessage)
                
                if str.lower(answer) == "y":
                    print(score)
                    twitter.update_status(status=posmessage)

                elif str.lower(answer) == "n":
                    print(score)
                    twitter.update_status(status=posmessage)

            if(score < 0):
                #if 2 minutes no input, continue with negmessage - change later
                print(data['text'])
                print(score)

                try:
                    answer = timer.input_with_timeout("Is this tweet actually negative? Y for yes, N for no: ", 10)
                except timer.TimeoutExpired:
                    print(score)
                    twitter.update_status(status=posmessage)
                
                if str.lower(answer) == "y":
                    print(score)
                    twitter.update_status(status=posmessage)

                elif str.lower(answer) == "n":
                    print(score)
                    twitter.update_status(status=posmessage)
            

    def on_error(self, status_code, data):
        print(status_code)

stream = MyStreamer(API_KEY, API_SECRET, OAUTH_TOKEN, OAUTH_TOKEN_SECRET)
stream.statuses.filter(follow='1004873339913977857') #25073877