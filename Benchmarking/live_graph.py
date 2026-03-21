import subprocess
import matplotlib
matplotlib.use('TkAgg')  # must be before any other matplotlib import
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.ticker as ticker
import tkinter as tk
import os

# -----------------------------------------------------------------------
# ADT options — add new ones here as you implement them
# -----------------------------------------------------------------------

ADT_OPTIONS = {
    "Array Stack":       "ArrayStack",
    "SLL Queue":         "SLLQueue",
    "DL List":           "DLList",
    "Array Deque":       "ArrayDeque",
    "Meldable Heap":     "MeldableHeap",
    "Skip List":         "Skiplist",
    "Chained Hash Set":  "ChainedHashSet",
    "Red Black Tree":    "RedBlackTree",
    "Adjacency Matrix":  "AdjacencyMatrix",
}

ADT_TITLES = {
    "ArrayStack":       "Array Stack: Bulk Push Performance",
    "SLLQueue":         "SLL Queue: Enqueue + Dequeue Performance",
    "DLList":           "DL List: Add + Remove Full Cycle",
    "ArrayDeque":       "Array Deque: Both Ends Performance",
    "MeldableHeap":     "Meldable Heap: Enqueue Performance",
    "Skiplist":         "Skip List: Add Performance",
    "ChainedHashSet":   "Chained Hash Set: Add Performance",
    "RedBlackTree":     "Red Black Tree: Add Performance",
    "AdjacencyMatrix":  "Adjacency Matrix: Add Edge Performance",
}

APP_BG      = '#F8FAFC'
CHART_BG    = '#FFFFFF'
TEXT_COLOR  = '#94A3B8'
TITLE_COLOR = '#334155'
LINE_COLOR  = '#8B5CF6'
GRID_COLOR  = '#F1F5F9'
BTN_BG      = '#8B5CF6'
BTN_FG      = '#FFFFFF'
BTN_HOVER   = '#7C3AED'

# -----------------------------------------------------------------------
# Popup selector window
# -----------------------------------------------------------------------
def show_selector():
    """Opens a popup window with buttons for each ADT. Returns the chosen ADT key."""

    root = tk.Tk()
    chosen = tk.StringVar(value="")

    root.title("DSA Benchmarker")
    root.configure(bg=APP_BG)
    root.resizable(False, False)

    # center the window — increased height to handle Windows display scaling
    window_width, window_height = 360, 550
    screen_width  = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()
    x = (screen_width  // 2) - (window_width  // 2)
    y = (screen_height // 2) - (window_height // 2)
    root.geometry(f"{window_width}x{window_height}+{x}+{y}")

    # title label
    tk.Label(
        root,
        text="DSA Benchmarker",
        font=("Century Gothic", 16, "bold"),
        bg=APP_BG,
        fg=TITLE_COLOR
    ).pack(pady=(30, 4))

    # subtitle label
    tk.Label(
        root,
        text="Select a data structure to benchmark",
        font=("Century Gothic", 10),
        bg=APP_BG,
        fg=TEXT_COLOR
    ).pack(pady=(0, 24))

    # one button per ADT
    for label, key in ADT_OPTIONS.items():
        btn = tk.Button(
            root,
            text=label,
            font=("Century Gothic", 11, "bold"),
            bg=BTN_BG,
            fg=BTN_FG,
            activebackground=BTN_HOVER,
            activeforeground=BTN_FG,
            relief="flat",
            cursor="hand2",
            width=22,
            height=1,
            command=lambda k=key: [chosen.set(k), root.destroy()]
        )
        btn.pack(pady=6)

    root.mainloop()
    return chosen.get()

# -----------------------------------------------------------------------
# Main
# -----------------------------------------------------------------------
adt_choice = show_selector()

# if user closes the popup without choosing, exit cleanly
if not adt_choice:
    exit(0)

# run benchmark.exe and pipe its output into this script
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

process = subprocess.Popen(
    [os.path.join(BASE_DIR, "benchmark.exe"), adt_choice],
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    text=True
)

# -----------------------------------------------------------------------
# Graph setup
# -----------------------------------------------------------------------
plt.rcParams['font.family'] = 'sans-serif'
plt.rcParams['font.sans-serif'] = ['Century Gothic', 'Trebuchet MS', 'Arial Rounded MT Bold', 'sans-serif']

fig, ax = plt.subplots(figsize=(10, 6))
fig.patch.set_facecolor(APP_BG)
ax.set_facecolor(CHART_BG)

plt.show(block=False)
if fig.canvas.manager is not None:
    fig.canvas.manager.set_window_title("DSA Benchmarker")

ax.set_title(ADT_TITLES.get(adt_choice, adt_choice), fontsize=16, fontweight='bold', color=TITLE_COLOR, pad=20)
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
    # Set the limit to 20,000 for Adjacency Matrix, otherwise 1,100,000
    if adt_choice == "AdjacencyMatrix":
        ax.set_xlim(0, 20000)
    else:
        ax.set_xlim(0, 1100000)
        
    ax.set_ylim(0, 0.006)
    ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, pos: f'{int(x):,}'))
    return line,

def update(frame):
    global fill_poly

    # read from the benchmark process instead of stdin
    if process.stdout is not None:
        line_str = process.stdout.readline()
    else:
        return line,

    if line_str:
        try:
            n_str, t_str = line_str.strip().split(',')
            n = float(n_str)
            t = float(t_str)

            x_data.append(n)
            y_data.append(t)

            line.set_data(x_data, y_data)

            ax.set_ylim(0, max(y_data) * 1.2)  # auto scale y axis

            # only redraw fill every 10 frames to reduce lag
            if len(x_data) % 10 == 0:
                if fill_poly is not None:
                    fill_poly.remove()
                fill_poly = ax.fill_between(x_data, y_data, 0, color=LINE_COLOR, alpha=0.15)

        except ValueError:
            pass

    return line,

# interval at 50ms (20 FPS) to keep things smooth without lag
ani = animation.FuncAnimation(fig, update, init_func=init, blit=False, interval=50, cache_frame_data=False)

plt.tight_layout()
plt.show()