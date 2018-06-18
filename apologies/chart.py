from matplotlib import pyplot

def chart(positive, neutral, negative): 
        # Data to plot
        labels = ['positive', 'neutral', 'negative']
        sizes = [positive, neutral, negative]
        colors = ['green', 'yellow', 'red']
        explode = (0, 0, 0)
        
        # Plot
        pyplot.pie(sizes, explode=explode, labels=labels, colors=colors,
                autopct='%1.1f%%', shadow=True, startangle=140)
        pyplot.title('Trump Tweets')
        
        pyplot.axis('equal')
        pyplot.savefig('chart.png', bbox_inches='tight')