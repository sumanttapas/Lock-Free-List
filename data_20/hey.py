import re
import plotly 
plotly.tools.set_credentials_file(username='rsingh61', api_key='56v614d65q')
import plotly.plotly as py
import plotly.graph_objs as go
with open('Final_m_lf.c') as f:
    lines = f.read()
a=re.split('=|\n',lines)
alpha=a[0:][::2]
alpha=alpha[:11]
beta=a[1:][::2]
trace0 = go.Scatter(
    x = alpha,
    y = beta,
    name = 'Lockfree',
    line = dict(
        color = ('rgb(205, 12, 24)'),
        width = 4)
)
with open('Final_m_wlf.c') as f:
    lines = f.read()
a=re.split('=|\n',lines)
alpha=a[0:][::2]
alpha=alpha[:11]
beta=a[1:][::2]
trace1 = go.Scatter(
    x = alpha,
    y = beta,
    name = 'Locked',
    line = dict(
        color = ('rgb(22, 96, 167)'),
        width = 4,)
)
data = [trace0, trace1]

# Edit the layout
layout = dict(title = 'Average High and Low Temperatures in New York',
              xaxis = dict(title = 'Temperature (degrees F)'),
              yaxis = dict(title = 'Month'),
              )

# Plot and embed in ipython notebook!
fig = dict(data=data, layout=layout)
py.iplot(fig, filename='styled-line')
