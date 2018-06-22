from twython import Twython, TwythonAuthError, TwythonError, TwythonRateLimitError, TwythonStreamer
from analyzer import analyze
from chart import chart
import timer

def sentiment(Data, text, negative, positive, twitter):
    negmessage = [Data[0], ' Apologies for Trump and his rudeness today. @realDonaldTrump']
    posmessage = [Data[1], ' Wow, Donald Trump managed to actually be decent today! @realDonaldTrump']
        
    score = analyze(str.lower(text), negative, positive)

    #if positive sentiment
    if(score > 0):
        print(text)
        print(score)

        #if 5 minutes no input to verify, continue with posmessage - change later
        try:
            answer = timer.input_with_timeout("Is this tweet actually positive? Y for yes, N for no: ", 10)
        except timer.TimeoutExpired:
            print(score)
            Data[2] = int(Data[2]) + 1
            Data[0] = int(Data[0]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=posmessage, media_ids=[response['media_id']])
                    
        if str.lower(answer) == "y":
            print(score)
            Data[2] = int(Data[2]) + 1
            Data[0] = int(Data[0]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=posmessage, media_ids=[response['media_id']])

        elif str.lower(answer) == "n":
            print(score)
            Data[4] = int(Data[4]) + 1
            Data[1] = int(Data[1]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=negmessage, media_ids=[response['media_id']])

    #if neutral sentiment
    if(score == 0):
        print(text)
        print(score)

        #if 5 minutes no input to verify, continue with posmessage - change later
        try:
            answer = timer.input_with_timeout("Is this tweet actually neutral? Y for yes, N for no: ", 10)

        except timer.TimeoutExpired:
            print(score)
            Data[3] = int(Data[3]) + 1
            Data[0] = int(Data[0]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=posmessage, media_ids=[response['media_id']])

        if str.lower(answer) == "y":
            print(score)
            Data[3] = int(Data[3]) + 1
            Data[0] = int(Data[0]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=posmessage, media_ids=[response['media_id']])

        elif str.lower(answer) == "n":
            print(score)
            Data[4] = int(Data[4]) + 1
            Data[1] = int(Data[1]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=negmessage, media_ids=[response['media_id']])

    #if negative sentiment
    if(score < 0):
        #if 5 minutes no input to verify, continue with negmessage - change later
        print(text)
        print(score)

        try:
            answer = timer.input_with_timeout("Is this tweet actually negative? Y for yes, N for no, p for neutral: ", 10)
        except timer.TimeoutExpired:
            print(score)
            Data[4] = int(Data[4]) + 1
            Data[1] = int(Data[1]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=negmessage, media_ids=[response['media_id']])
                    
        if str.lower(answer) == "y":
            print(score)
            Data[4] = int(Data[4]) + 1
            Data[1] = int(Data[1]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=negmessage, media_ids=[response['media_id']])

        elif str.lower(answer) == "n":
            print(score)
            Data[2] = int(Data[2]) + 1
            Data[0] = int(Data[0]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=posmessage, media_ids=[response['media_id']])

        elif str.lower(answer) == "p":
            print(score)
            Data[3] = int(Data[3]) + 1
            Data[0] = int(Data[0]) + 1

            chart(Data[2], Data[3], Data[4])
            photo = open('chart.png', 'rb')
            response = twitter.upload_media(media=photo)
            twitter.update_status(status=posmessage, media_ids=[response['media_id']])