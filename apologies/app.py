from twython import Twython, TwythonAuthError, TwythonError, TwythonRateLimitError, TwythonStreamer
from analyzer import analyze
from chart import chart
import timer
from sentiment import sentiment

#set up OAuth
API_KEY = ' ' 
API_SECRET = ' ' 
OAUTH_TOKEN = ' ' 
OAUTH_TOKEN_SECRET = ' '

twitter = Twython(API_KEY, API_SECRET, OAUTH_TOKEN, OAUTH_TOKEN_SECRET)

#set up path to references
negPath = 'negative-words.txt'
posPath = 'positive-words.txt'

#open references, read into lists
negWords = open(negPath,'r')
posWords = open(posPath,'r')

negative = negWords.readlines()
positive = posWords.readlines()

#get rid of the "/n"
for n in range(4783):   #negative reference
    convertneg = ""
    convertneg = negative[n]
    convertneg = convertneg[:-1]
    negative[n] = convertneg

for p in range(2006):   #positive reference
    convertpos = ""
    convertpos = positive[p]
    convertpos = convertpos[:-1]
    positive[p] = convertpos

#open data file, check for previous data
dataPath = 'data.txt'
dataFile = open(dataPath, 'r')

Data = dataFile.readlines()

pos = Data[2]
neutral = Data[3]
neg = Data[4]

#get rid of the "/n"
for d in range(6):
    convertdat = ""
    convertdat = Data[d]
    convertdat = convertdat[:-1]
    Data[d] = convertdat

#check if there have been any other tweets since program was stopped - TODO
previous = twitter.get_user_timeline(screen_name = '@realDonaldTrump') 
t = 0

while Data[5] != previous[t]['created_at']:
    sentiment(Data, previous[t]['text'], negative, positive, twitter)
    t = t + 1

#update timestamp
Data[5] = previous[0]['created_at']
reinit = (dataPath, "w")
reinit.write = (Data)

class MyStreamer(TwythonStreamer):
    def on_success(self, data):
        sentiment(Data, data['text'], negative, positive, twitter) 

        #save timestamp, new data for positive, negative, neutral
        timestamp = twitter.get_user_timeline(screen_name = '@realDonaldTrump')
        Data[5] = timestamp[0]['created_at']
        update = (dataPath, "w")
        update.write = (Data)

    def on_error(self, status_code, data):
        print(status_code)

stream = MyStreamer(API_KEY, API_SECRET, OAUTH_TOKEN, OAUTH_TOKEN_SECRET)
stream.statuses.filter(follow='25073877') #@realDonaldTrump