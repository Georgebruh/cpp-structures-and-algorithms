import sys
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.ticker as ticker

plt.rcParams['font.family'] = 'sans-serif'
plt.rcParams['font.sans-serif'] = ['Century Gothic', 'Trebuchet MS', 'Arial Rounded MT Bold', 'sans-serif']

APP_BG = '#F8FAFC'
CHART_BG = '#FFFFFF'
TEXT_COLOR = '#94A3B8'
TITLE_COLOR = '#334155'
LINE_COLOR = '#8B5CF6'
GRID_COLOR = '#F1F5F9'

fig, ax = plt.subplots(figsize=(10, 6))
fig.patch.set_facecolor(APP_BG)
ax.set_facecolor(CHART_BG)
fig.canvas.manager.set_window_title("DSA Benchmarker")
ax.set_title("Array Stack: Bulk Push Performance", fontsize=16, fontweight='bold', color=TITLE_COLOR, pad=20)
ax.set_xlabel("Number of Elements (N)", fontsize=11, fontweight='bold', color=TEXT_COLOR, labelpad=10)
ax.set_ylabel("Time (Seconds)", fontsize=11, fontweight='bold', color=TEXT_COLOR, labelpad=10)

ax.tick_params(colors=TEXT_COLOR, length=0, pad=8) 
ax.grid(axis='y', color=GRID_COLOR, linestyle='--', linewidth=1.5) 
ax.grid(axis='x', visible=False) 
for spine in ax.spines.values():
    spine.set_visible(False)

x_data, y_data = [], []
fill_poly = None 

line, = ax.plot([], [], color=LINE_COLOR, linewidth=3)

def init():
    ax.set_xlim(0, 1000000) 
    ax.set_ylim(0, 0.0045)    
    
    ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, pos: f'{int(x):,}'))
    return line,

def update(frame):
    global fill_poly
    line_str = sys.stdin.readline()
    
    if line_str:
        try:
            n_str, t_str = line_str.strip().split(',')
            n = float(n_str)
            t = float(t_str)
            
            x_data.append(n)
            y_data.append(t)
            
            line.set_data(x_data, y_data)
            
            if fill_poly is not None:
                fill_poly.remove() 
            fill_poly = ax.fill_between(x_data, y_data, 0, color=LINE_COLOR, alpha=0.15)
                
        except ValueError:
            pass 
            
    return line,

ani = animation.FuncAnimation(fig, update, init_func=init, blit=False, interval=10)

plt.tight_layout()
plt.show()