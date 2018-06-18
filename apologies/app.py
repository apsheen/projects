from twython import Twython, TwythonAuthError, TwythonError, TwythonRateLimitError, TwythonStreamer
from analyzer import analyze
from chart import chart
import timer

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

data = dataFile.readlines()

pos = data[2]
neutral = data[3]
negative = data[4]

#get rid of the "/n"
for d in range(1):
    convertneg = ""
    convertneg = negative[n]
    convertneg = convertneg[:-1]
    negative[n] = convertneg

#use data to carry on where the program stopped
negmessage = [data[0], ' Apologies for Trump and his rudeness today. @realDonaldTrump']
posmessage = [data[1], ' Wow, Donald Trump managed to actually be decent today! @realDonaldTrump']

#check if there have been any other tweets since program was stopped
#TODO

class MyStreamer(TwythonStreamer):
    def on_success(self, data):
        if 'text' in data:
            #call sentiment analysis
            score = analyze(str.lower(data['text']), negative, positive)

            #if good/neutral sentiment
            if(score >= 0):
                print(data['text'])
                print(score)

                #if 5 minutes no input to verify, continue with posmessage - change later
                try:
                    answer = timer.input_with_timeout("Is this tweet actually positive/neutral? Y for yes, N for no: ", 10)
                except timer.TimeoutExpired:
                    print(score)

                    chart(pos, neutral, negative)
                    photo = open('chart.png', 'rb')
                    response = twitter.upload_media(media=photo)
                    twitter.update_status(status=negmessage, media_ids=[response['media_id']])
                
                if str.lower(answer) == "y":
                    print(score)

                    chart(pos, neutral, negative)
                    photo = open('chart.png', 'rb')
                    response = twitter.upload_media(media=photo)
                    twitter.update_status(status=negmessage, media_ids=[response['media_id']])

                elif str.lower(answer) == "n":
                    print(score)

                    chart(pos, neutral, negative)
                    photo = open('chart.png', 'rb')
                    response = twitter.upload_media(media=photo)
                    twitter.update_status(status=negmessage, media_ids=[response['media_id']])

            #if bad sentiment
            if(score < 0):
                #if 5 minutes no input to verify, continue with negmessage - change later
                print(data['text'])
                print(score)

                try:
                    answer = timer.input_with_timeout("Is this tweet actually negative? Y for yes, N for no: ", 10)
                except timer.TimeoutExpired:
                    print(score)

                    chart(pos, neutral, negative)
                    photo = open('chart.png', 'rb')
                    response = twitter.upload_media(media=photo)
                    twitter.update_status(status=negmessage, media_ids=[response['media_id']])
                
                if str.lower(answer) == "y":
                    print(score)

                    chart(pos, neutral, negative)
                    photo = open('chart.png', 'rb')
                    response = twitter.upload_media(media=photo)
                    twitter.update_status(status=negmessage, media_ids=[response['media_id']])

                elif str.lower(answer) == "n":
                    print(score)

                    chart(pos, neutral, negative)
                    photo = open('chart.png', 'rb')
                    response = twitter.upload_media(media=photo)
                    twitter.update_status(status=negmessage, media_ids=[response['media_id']])

                #save timestamp, new data for positive, negative, neutral
                #TODO

    def on_error(self, status_code, data):
        print(status_code)

stream = MyStreamer(API_KEY, API_SECRET, OAUTH_TOKEN, OAUTH_TOKEN_SECRET)
stream.statuses.filter(follow='25073877') # @realDonaldTrump