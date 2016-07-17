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
trace1 = go.Bar(
    x=alpha,
    y=beta,
    name='Lock Free'
)
with open('Final_m_wlf.c') as f:
    lines = f.read()
a=re.split('=|\n',lines)
alpha=a[0:][::2]
alpha=alpha[:11]
beta=a[1:][::2]
trace2 = go.Bar(
  x=alpha,
  y=beta,
    name='Locked'
)

data = [trace1, trace2]
layout = go.Layout(
    barmode='group'
)

fig = go.Figure(data=data, layout=layout)
py.iplot(fig, filename='20threads')
