import yfinance as yf

#define the ticker symbol
tickerSymbol = 'TSLA'

#get data on this ticker
tickerData = yf.Ticker(tickerSymbol)

#get the historical prices for this ticker
#tickerDf = tickerData.history(period='1d', start='2020-1-1', end='2020-10-30')

tickerDf = tickerData.history(period='ytd')
#see your data
for col in tickerDf['Close']:
    print(col),
