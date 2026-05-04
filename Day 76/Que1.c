Hotel Management System - Tkinter GUI
College Project - Python with SQLite + Tkinter
"""

import sqlite3
import datetime
import tkinter as tk
from tkinter import ttk, messagebox, font


# ─────────────────────────────────────────
# THEME CONSTANTS
# ─────────────────────────────────────────

BG_DARK      = "#0F1923"   # deep navy
BG_CARD      = "#1A2535"   # card background
BG_SIDEBAR   = "#111D2B"   # sidebar
ACCENT       = "#C9A84C"   # gold accent
ACCENT_DARK  = "#A07830"
TEXT_MAIN    = "#EAE6DC"   # warm white
TEXT_MUTED   = "#8A96A8"
TEXT_DARK    = "#0F1923"
SUCCESS      = "#4CAF82"
DANGER       = "#E05C5C"
INFO         = "#4A90C4"
BORDER       = "#263347"

FONT_TITLE  = ("Georgia", 22, "bold")
FONT_HEADER = ("Georgia", 13, "bold")
FONT_LABEL  = ("Helvetica", 10)
FONT_BOLD   = ("Helvetica", 10, "bold")
FONT_SMALL  = ("Helvetica", 9)
FONT_MONO   = ("Courier", 10)


# ─────────────────────────────────────────
# DATABASE
# ─────────────────────────────────────────

def init_db():
    conn = sqlite3.connect("hotel.db")
    cur = conn.cursor()
    cur.execute("""CREATE TABLE IF NOT EXISTS rooms (
    room_no INTEGER PRIMARY KEY, 
    room_type TEXT NOT NULL,
    price REAL NOT NULL, 
    status TEXT DEFAULT 'Available',
    hk_status TEXT DEFAULT 'Clean')""") 
    cur.execute("""CREATE TABLE IF NOT EXISTS customers (
        customer_id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL, phone TEXT NOT NULL,
        country TEXT DEFAULT 'India', meal_plan TEXT DEFAULT 'BB')""")
    cur.execute("""CREATE TABLE IF NOT EXISTS bookings (
        booking_id INTEGER PRIMARY KEY AUTOINCREMENT,
        customer_id INTEGER, room_no INTEGER,
        check_in TEXT, check_out TEXT,
        adults INTEGER DEFAULT 1, children INTEGER DEFAULT 0,
        status TEXT DEFAULT 'Booked',
        FOREIGN KEY(customer_id) REFERENCES customers(customer_id),
        FOREIGN KEY(room_no) REFERENCES rooms(room_no))""")
    cur.execute("""CREATE TABLE IF NOT EXISTS bills (
        bill_id INTEGER PRIMARY KEY AUTOINCREMENT,
        booking_id INTEGER, total_amt REAL, paid TEXT DEFAULT 'No',
        FOREIGN KEY(booking_id) REFERENCES bookings(booking_id))""")
    cur.execute("SELECT COUNT(*) FROM rooms")
    if cur.fetchone()[0] == 0:
        cur.executemany("INSERT INTO rooms (room_no, room_type, price) VALUES (?,?,?)", [
            (101,'Single',1500),(102,'Single',1500),(103,'Double',2500),
            (104,'Double',2500),(105,'Suite',5000),(201,'Single',1800),
            (202,'Double',2800),(203,'Suite',5500)])
    conn.commit(); conn.close()

def calculate_stay_price(room_type, nights):
    # Rule: Single (350), Double (700), Suite (1000)
    # Weekly: Single (2000), Double (3500)
    # Monthly (30+ days): Single (8000), Double (10000)
    
    total = 0
    remaining_nights = nights

    if room_type == 'Single':
        months = remaining_nights // 30
        remaining_nights %= 30
        weeks = remaining_nights // 7
        days = remaining_nights % 7
        total = (months * 8000) + (weeks * 2000) + (days * 350)
        
    elif room_type == 'Double':
        months = remaining_nights // 30
        remaining_nights %= 30
        weeks = remaining_nights // 7
        days = remaining_nights % 7
        total = (months * 10000) + (weeks * 3500) + (days * 700)
        
    else: # Suite or others (using daily rate for now)
        total = nights * 1000
        
    return total

def get_conn():
    return sqlite3.connect("hotel.db")


# ─────────────────────────────────────────
# HELPER WIDGETS
# ─────────────────────────────────────────

def styled_frame(parent, bg=BG_CARD, padx=0, pady=0):
    return tk.Frame(parent, bg=bg, padx=padx, pady=pady)

def label(parent, text, font=FONT_LABEL, fg=TEXT_MAIN, bg=BG_CARD, **kw):
    return tk.Label(parent, text=text, font=font, fg=fg, bg=bg, **kw)

def entry(parent, width=24, textvariable=None):
    e = tk.Entry(parent, width=width, font=FONT_LABEL,
                 bg="#1F2E40", fg=TEXT_MAIN, insertbackground=ACCENT,
                 relief="flat", bd=0, highlightthickness=1,
                 highlightbackground=BORDER, highlightcolor=ACCENT)
    if textvariable:
        e.config(textvariable=textvariable)
    return e

def combo(parent, values, textvariable=None, width=22):
    style = ttk.Style()
    style.theme_use("clam")
    style.configure("Hotel.TCombobox",
        fieldbackground="#1F2E40", background="#1F2E40",
        foreground=TEXT_MAIN, arrowcolor=ACCENT,
        bordercolor=BORDER, lightcolor=BORDER, darkcolor=BORDER)
    c = ttk.Combobox(parent, values=values, width=width,
                     font=FONT_LABEL, style="Hotel.TCombobox", state="readonly")
    if textvariable:
        c.config(textvariable=textvariable)
    return c

def gold_btn(parent, text, command, width=16, bg=ACCENT, fg=TEXT_DARK):
    b = tk.Button(parent, text=text, command=command,
                  font=FONT_BOLD, bg=bg, fg=fg,
                  activebackground=ACCENT_DARK, activeforeground=TEXT_DARK,
                  relief="flat", cursor="hand2", padx=10, pady=6, width=width)
    b.bind("<Enter>", lambda e: b.config(bg=ACCENT_DARK))
    b.bind("<Leave>", lambda e: b.config(bg=bg))
    return b

def danger_btn(parent, text, command, width=14):
    return gold_btn(parent, text, command, width=width, bg=DANGER, fg=TEXT_MAIN)

def section_title(parent, text):
    f = tk.Frame(parent, bg=BG_CARD)
    tk.Label(f, text=text, font=FONT_HEADER, fg=ACCENT, bg=BG_CARD).pack(side="left")
    tk.Frame(f, bg=ACCENT, height=2).pack(side="left", fill="x", expand=True, padx=(10,0), pady=8)
    return f

def build_treeview(parent, columns, col_widths=None):
    style = ttk.Style()
    style.configure("Hotel.Treeview",
        background=BG_DARK, foreground=TEXT_MAIN,
        fieldbackground=BG_DARK, rowheight=26,
        font=FONT_SMALL, borderwidth=0)
    style.configure("Hotel.Treeview.Heading",
        background=BG_CARD, foreground=ACCENT,
        font=FONT_BOLD, relief="flat")
    style.map("Hotel.Treeview",
        background=[("selected", ACCENT)],
        foreground=[("selected", TEXT_DARK)])

    frame = tk.Frame(parent, bg=BG_DARK)
    scroll = ttk.Scrollbar(frame, orient="vertical")
    tv = ttk.Treeview(frame, columns=columns, show="headings",
                      yscrollcommand=scroll.set, style="Hotel.Treeview")
    scroll.config(command=tv.yview)

    for i, col in enumerate(columns):
        w = col_widths[i] if col_widths else 120
        tv.heading(col, text=col)
        tv.column(col, width=w, anchor="center")

    tv.pack(side="left", fill="both", expand=True)
    scroll.pack(side="right", fill="y")
    return frame, tv

def form_row(parent, lbl_text, widget):
    row = tk.Frame(parent, bg=BG_CARD)
    tk.Label(row, text=lbl_text, font=FONT_LABEL, fg=TEXT_MUTED, bg=BG_CARD,
             width=18, anchor="w").pack(side="left", padx=(0,8))
    widget.pack(side="left")
    return row

def status_badge(parent, text):
    colors = {
        "Available": SUCCESS, "Occupied": DANGER,
        "Booked": INFO, "Checked-Out": TEXT_MUTED,
        "Cancelled": DANGER, "Yes": SUCCESS, "No": DANGER, "Pending": ACCENT
    }
    color = colors.get(text, TEXT_MUTED)
    return tk.Label(parent, text=f"  {text}  ", font=FONT_SMALL,
                    bg=color, fg=TEXT_DARK if text in ("Available","Yes") else TEXT_MAIN,
                    relief="flat", padx=4)


# ─────────────────────────────────────────
# MAIN APPLICATION
# ─────────────────────────────────────────

class HotelApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Hotel Management System")
        self.geometry("1100x700")
        self.minsize(900, 600)
        self.configure(bg=BG_DARK)
        self.resizable(True, True)
        init_db()
        self._build_layout()
        self._show_page("dashboard")

    def _build_layout(self):
        # ── Sidebar ──
        self.sidebar = tk.Frame(self, bg=BG_SIDEBAR, width=200)
        self.sidebar.pack(side="left", fill="y")
        self.sidebar.pack_propagate(False)

        # Logo area
        logo_f = tk.Frame(self.sidebar, bg=BG_SIDEBAR, pady=24)
        logo_f.pack(fill="x")
        tk.Label(logo_f, text="🏨", font=("Helvetica", 28), bg=BG_SIDEBAR, fg=ACCENT).pack()
        tk.Label(logo_f, text="GRAND HOTEL", font=("Georgia", 11, "bold"),
                 bg=BG_SIDEBAR, fg=ACCENT).pack()
        tk.Label(logo_f, text="Management Suite", font=("Helvetica", 8),
                 bg=BG_SIDEBAR, fg=TEXT_MUTED).pack()
        tk.Frame(self.sidebar, bg=BORDER, height=1).pack(fill="x", padx=16)

        # Nav buttons
        nav_items = [
            ("dashboard", "⊞  Dashboard"),
            ("rooms",     "🚪  Rooms"),
            ("customers", "👤  Customers"),
            ("bookings",  "📋  Bookings"),
            ("billing",   "💳  Billing"),
            ("housekeeping", "🧹  Housekeeping"),
        ]
        self.nav_btns = {}
        nav_frame = tk.Frame(self.sidebar, bg=BG_SIDEBAR, pady=16)
        nav_frame.pack(fill="x")
        for key, text in nav_items:
            btn = tk.Button(nav_frame, text=text, font=FONT_LABEL,
                            bg=BG_SIDEBAR, fg=TEXT_MUTED, relief="flat",
                            anchor="w", padx=20, pady=10, cursor="hand2",
                            activebackground=BG_CARD, activeforeground=ACCENT,
                            command=lambda k=key: self._show_page(k))
            btn.pack(fill="x", pady=1)
            self.nav_btns[key] = btn

        # ── Content area ──
        self.content = tk.Frame(self, bg=BG_DARK)
        self.content.pack(side="left", fill="both", expand=True)

        self.pages = {}
        for PageClass, key in [
            (DashboardPage, "dashboard"),
            (RoomsPage,     "rooms"),
            (CustomersPage, "customers"),
            (BookingsPage,  "bookings"),
            (BillingPage,   "billing"),
            (HousekeepingPage, "housekeeping"),
        ]:
            page = PageClass(self.content, self)
            page.place(relx=0, rely=0, relwidth=1, relheight=1)
            self.pages[key] = page
           

    def refresh(self):
        self.tv.delete(*self.tv.get_children())
        conn = get_conn(); cur = conn.cursor()
        cur.execute("SELECT room_no, room_type, status, hk_status FROM rooms")
        for row in cur.fetchall():
            tag = "dirty" if row[3] == "Dirty" else "clean"
            if row[3] == "Service Requested": tag = "request"
            self.tv.insert("", "end", values=row, tags=(tag,))
        
        self.tv.tag_configure("dirty", background="#2E1A1A") # Reddish
        self.tv.tag_configure("clean", background="#152218") # Greenish
        self.tv.tag_configure("request", background="#2E2A12") # Yellowish
        conn.close()

    def _update_hk(self, new_status):
        sel = self.tv.selection()
        if not sel: return
        room_no = self.tv.item(sel[0])['values'][0]
        conn = get_conn(); cur = conn.cursor()
        cur.execute("UPDATE rooms SET hk_status=? WHERE room_no=?", (new_status, room_no))
        conn.commit(); conn.close()
        self.refresh()

    def _show_page(self, key):
        for k, btn in self.nav_btns.items():
            if k == key:
                btn.config(bg=BG_CARD, fg=ACCENT, font=FONT_BOLD)
            else:
                btn.config(bg=BG_SIDEBAR, fg=TEXT_MUTED, font=FONT_LABEL)
        self.pages[key].tkraise()
        if hasattr(self.pages[key], "refresh"):
            self.pages[key].refresh()


# ─────────────────────────────────────────
# DASHBOARD PAGE
# ─────────────────────────────────────────

class DashboardPage(tk.Frame):
    def __init__(self, parent, app):
        super().__init__(parent, bg=BG_DARK)
        self.app = app
        self._build()

    def _build(self):
        # Header
        hdr = tk.Frame(self, bg=BG_DARK, pady=20, padx=30)
        hdr.pack(fill="x")
        tk.Label(hdr, text="Dashboard", font=FONT_TITLE, fg=ACCENT, bg=BG_DARK).pack(side="left")
        self.date_lbl = tk.Label(hdr, text="", font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_DARK)
        self.date_lbl.pack(side="right", pady=8)
        self._update_clock()

        # Stat cards
        self.cards_frame = tk.Frame(self, bg=BG_DARK, padx=30)
        self.cards_frame.pack(fill="x", pady=(0, 20))

        # Recent bookings
        body = tk.Frame(self, bg=BG_DARK, padx=30)
        body.pack(fill="both", expand=True)
        section_title(body, "Recent Bookings").pack(fill="x", pady=(0,10))
        cols = ["Booking ID", "Guest", "Room", "Check-In", "Check-Out", "Status"]
        widths = [90, 160, 70, 110, 110, 110]
        tv_frame, self.tv = build_treeview(body, cols, widths)
        tv_frame.pack(fill="both", expand=True, pady=(0,20))

    def _update_clock(self):
        now = datetime.datetime.now()
        self.date_lbl.config(text=now.strftime("  %A, %d %B %Y   %H:%M"))
        self.after(1000, self._update_clock)

    def _stat_card(self, parent, icon, title, value, color):
        f = tk.Frame(parent, bg=BG_CARD, padx=20, pady=16,
                     highlightthickness=1, highlightbackground=BORDER)
        f.pack(side="left", padx=(0,14), pady=4, fill="y")
        tk.Label(f, text=icon, font=("Helvetica", 24), bg=BG_CARD, fg=color).pack(anchor="w")
        tk.Label(f, text=str(value), font=("Georgia", 22, "bold"),
                 bg=BG_CARD, fg=color).pack(anchor="w")
        tk.Label(f, text=title, font=FONT_SMALL, bg=BG_CARD, fg=TEXT_MUTED).pack(anchor="w")

    def refresh(self):
        # Clear old cards
        for w in self.cards_frame.winfo_children():
            w.destroy()

        conn = get_conn(); cur = conn.cursor()
        cur.execute("SELECT COUNT(*) FROM rooms WHERE status='Available'")
        avail = cur.fetchone()[0]
        cur.execute("SELECT COUNT(*) FROM rooms WHERE status='Occupied'")
        occ = cur.fetchone()[0]
        cur.execute("SELECT COUNT(*) FROM bookings WHERE status='Booked'")
        active = cur.fetchone()[0]
        cur.execute("SELECT COALESCE(SUM(total_amt),0) FROM bills WHERE paid='Yes'")
        revenue = cur.fetchone()[0]
        conn.close()

        self._stat_card(self.cards_frame, "🚪", "Available Rooms", avail, SUCCESS)
        self._stat_card(self.cards_frame, "🏠", "Occupied Rooms",  occ,   DANGER)
        self._stat_card(self.cards_frame, "📋", "Active Bookings", active, INFO)
        self._stat_card(self.cards_frame, "💰", "Total Revenue",
                        f"₹{revenue:,.0f}", ACCENT)

        # Recent bookings
        self.tv.delete(*self.tv.get_children())
        conn = get_conn(); cur = conn.cursor()
        cur.execute("""SELECT b.booking_id, c.name, b.room_no, b.check_in, b.check_out, b.status
            FROM bookings b JOIN customers c ON b.customer_id=c.customer_id
            ORDER BY b.booking_id DESC LIMIT 15""")
        for row in cur.fetchall():
            tag = {"Booked": "info", "Checked-Out": "muted", "Cancelled": "danger"}.get(row[5], "")
            self.tv.insert("", "end", values=row, tags=(tag,))
        self.tv.tag_configure("info",   background="#1A2E40")
        self.tv.tag_configure("muted",  background="#1A2535")
        self.tv.tag_configure("danger", background="#2E1A1A")
        conn.close()


# ─────────────────────────────────────────
# ROOMS PAGE
# ─────────────────────────────────────────

class RoomsPage(tk.Frame):
    def __init__(self, parent, app):
        super().__init__(parent, bg=BG_DARK)
        self.app = app
        self._build()

    def _build(self):
        # Header
        hdr = tk.Frame(self, bg=BG_DARK, pady=20, padx=30)
        hdr.pack(fill="x")
        tk.Label(hdr, text="Room Management", font=FONT_TITLE, fg=ACCENT, bg=BG_DARK).pack(side="left")

        # Body
        body = tk.Frame(self, bg=BG_DARK)
        body.pack(fill="both", expand=True, padx=30)

        # Left: Table
        left = tk.Frame(body, bg=BG_DARK)
        left.pack(side="left", fill="both", expand=True, padx=(0,20))

        section_title(left, "All Rooms").pack(fill="x", pady=(0,10))
        cols = ["Room No", "Type", "Price/Night", "Status"]
        widths = [80, 100, 120, 110]
        tv_frame, self.tv = build_treeview(left, cols, widths)
        tv_frame.pack(fill="both", expand=True)

        # Right: Form
        right = tk.Frame(body, bg=BG_CARD, width=260, padx=20, pady=20,
                         highlightthickness=1, highlightbackground=BORDER)
        right.pack(side="right", fill="y")
        right.pack_propagate(False)

        # Add Room
        tk.Label(right, text="Add New Room", font=FONT_HEADER, fg=ACCENT, bg=BG_CARD).pack(anchor="w", pady=(0,14))

        self.v_room_no   = tk.StringVar()
        self.v_room_type = tk.StringVar(value="Single")
        self.v_price     = tk.StringVar()

        for lbl, var, widget_fn in [
            ("Room Number",  self.v_room_no,   lambda: entry(right, textvariable=self.v_room_no)),
            ("Price/Night",  self.v_price,     lambda: entry(right, textvariable=self.v_price)),
        ]:
            tk.Label(right, text=lbl, font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(8,2))
            widget_fn().pack(anchor="w", fill="x")

        tk.Label(right, text="Room Type", font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(8,2))
        combo(right, ["Single","Double","Suite","Deluxe"], self.v_room_type, width=22).pack(anchor="w")

        gold_btn(right, "➕  Add Room", self._add_room, width=22).pack(pady=(16,4), fill="x")

        # Divider
        tk.Frame(right, bg=BORDER, height=1).pack(fill="x", pady=14)

        # Update price
        tk.Label(right, text="Update Room Price", font=FONT_HEADER, fg=ACCENT, bg=BG_CARD).pack(anchor="w", pady=(0,10))
        self.v_upd_no    = tk.StringVar()
        self.v_upd_price = tk.StringVar()
        tk.Label(right, text="Room Number", font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(4,2))
        entry(right, textvariable=self.v_upd_no).pack(anchor="w", fill="x")
        tk.Label(right, text="New Price", font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(8,2))
        entry(right, textvariable=self.v_upd_price).pack(anchor="w", fill="x")
        gold_btn(right, "✏️  Update Price", self._update_price, width=22).pack(pady=(12,0), fill="x")

    def refresh(self):
        self.tv.delete(*self.tv.get_children())
        conn = get_conn(); cur = conn.cursor()
        cur.execute("SELECT room_no, room_type, price, status FROM rooms ORDER BY room_no")
        for row in cur.fetchall():
            tag = "avail" if row[3] == "Available" else "occ"
            self.tv.insert("", "end", values=(row[0], row[1], f"₹{row[2]:,.0f}", row[3]), tags=(tag,))
        self.tv.tag_configure("avail", background="#152218")
        self.tv.tag_configure("occ",   background="#2E1A1A")
        conn.close()

    def _add_room(self):
        try:
            rno   = int(self.v_room_no.get())
            price = float(self.v_price.get())
            rtype = self.v_room_type.get()
        except ValueError:
            messagebox.showerror("Input Error", "Please enter valid Room Number and Price.")
            return
        conn = get_conn(); cur = conn.cursor()
        try:
            cur.execute("INSERT INTO rooms (room_no, room_type, price) VALUES (?,?,?)", (rno, rtype, price))
            conn.commit()
            messagebox.showinfo("Success", f"Room {rno} added successfully!")
            self.v_room_no.set(""); self.v_price.set("")
            self.refresh()
        except sqlite3.IntegrityError:
            messagebox.showerror("Error", "Room number already exists!")
        conn.close()

    def _update_price(self):
        try:
            rtype = self.v_upd_type.get()
            price = float(self.v_upd_price.get())
        except ValueError:
            messagebox.showerror("Input Error", "Enter valid Price.")
            return
        conn = get_conn(); cur = conn.cursor()
        cur.execute("UPDATE rooms SET price=? WHERE room_type=?", (price, rtype))
        count = cur.rowcount
        if count>0:
            conn.commit()
            messagebox.showinfo("Success", f"Room {rtype} price updated to ₹{price}.")
            self.v_upd_no.set(""); self.v_upd_price.set("")
            self.refresh()
        else:
            messagebox.showerror("Error", "Room not found.")
        conn.close()


# ─────────────────────────────────────────
# CUSTOMERS PAGE
# ─────────────────────────────────────────

class CustomersPage(tk.Frame):
    def __init__(self, parent, app):
        super().__init__(parent, bg=BG_DARK)
        self.app = app
        self._build()

    def _build(self):
        hdr = tk.Frame(self, bg=BG_DARK, pady=20, padx=30)
        hdr.pack(fill="x")
        tk.Label(hdr, text="Customer Management", font=FONT_TITLE, fg=ACCENT, bg=BG_DARK).pack(side="left")

        body = tk.Frame(self, bg=BG_DARK)
        body.pack(fill="both", expand=True, padx=30)

        # Left table
        left = tk.Frame(body, bg=BG_DARK)
        left.pack(side="left", fill="both", expand=True, padx=(0,20))

        section_title(left, "All Customers").pack(fill="x", pady=(0,10))
        cols = ["ID", "Name", "Phone", "Country", "Meal Plan"]
        widths = [50, 160, 120, 100, 90]
        tv_frame, self.tv = build_treeview(left, cols, widths)
        tv_frame.pack(fill="both", expand=True)

        gold_btn(left, "📖 View Booking History", self._view_history, width=24).pack(pady=10, anchor="w")

        # Right form
        right = tk.Frame(body, bg=BG_CARD, width=260, padx=20, pady=20,
                         highlightthickness=1, highlightbackground=BORDER)
        right.pack(side="right", fill="y")
        right.pack_propagate(False)

        tk.Label(right, text="Add New Customer", font=FONT_HEADER, fg=ACCENT, bg=BG_CARD).pack(anchor="w", pady=(0,14))

        self.v_name    = tk.StringVar()
        self.v_phone   = tk.StringVar()
        self.v_country = tk.StringVar(value="India")
        self.v_meal    = tk.StringVar(value="BB")

        for lbl, var in [("Full Name", self.v_name), ("Phone Number", self.v_phone), ("Country", self.v_country)]:
            tk.Label(right, text=lbl, font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(8,2))
            entry(right, textvariable=var).pack(anchor="w", fill="x")

        tk.Label(right, text="Meal Plan", font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(8,2))
        combo(right, ["BB - Bed & Breakfast", "HB - Half Board", "FB - Full Board"],
              self.v_meal, width=22).pack(anchor="w")

        gold_btn(right, "➕  Add Customer", self._add_customer, width=22).pack(pady=(16,0), fill="x")

    def refresh(self):
        self.tv.delete(*self.tv.get_children())
        conn = get_conn(); cur = conn.cursor()
        cur.execute("SELECT customer_id, name, phone, country, meal_plan FROM customers ORDER BY customer_id DESC")
        for row in cur.fetchall():
            self.tv.insert("", "end", values=row)
        conn.close()

    def _add_customer(self):
        name    = self.v_name.get().strip()
        phone   = self.v_phone.get().strip()
        country = self.v_country.get().strip() or "India"
        meal    = self.v_meal.get().split(" ")[0]  # take 'BB', 'HB', or 'FB'
        if not name or not phone:
            messagebox.showerror("Error", "Name and Phone are required.")
            return
        conn = get_conn(); cur = conn.cursor()
        cur.execute("INSERT INTO customers (name, phone, country, meal_plan) VALUES (?,?,?,?)",
                    (name, phone, country, meal))
        conn.commit()
        cid = cur.lastrowid
        conn.close()
        messagebox.showinfo("Success", f"Customer added! ID: {cid}")
        self.v_name.set(""); self.v_phone.set("")
        self.refresh()

    def _view_history(self):
        sel = self.tv.selection()
        if not sel:
            messagebox.showinfo("Select Customer", "Please select a customer from the list.")
            return
        cid = self.tv.item(sel[0])["values"][0]
        win = tk.Toplevel(self)
        win.title(f"Booking History — Customer #{cid}")
        win.geometry("700x400")
        win.configure(bg=BG_DARK)
        tk.Label(win, text=f"Booking History for Customer ID: {cid}",
                 font=FONT_HEADER, fg=ACCENT, bg=BG_DARK).pack(pady=16, padx=20, anchor="w")
        cols = ["Booking ID", "Room", "Type", "Check-In", "Check-Out", "Status"]
        widths = [90, 70, 90, 110, 110, 110]
        f, tv = build_treeview(win, cols, widths)
        f.pack(fill="both", expand=True, padx=20, pady=(0,20))
        conn = get_conn(); cur = conn.cursor()
        cur.execute("""SELECT b.booking_id, r.room_no, r.room_type, b.check_in, b.check_out, b.status
            FROM bookings b JOIN rooms r ON b.room_no=r.room_no
            WHERE b.customer_id=? ORDER BY b.booking_id DESC""", (cid,))
        for row in cur.fetchall():
            tv.insert("", "end", values=row)
        conn.close()


# ─────────────────────────────────────────
# BOOKINGS PAGE
# ─────────────────────────────────────────

class BookingsPage(tk.Frame):
    def __init__(self, parent, app):
        super().__init__(parent, bg=BG_DARK)
        self.app = app
        self._build()

    def _build(self):
        hdr = tk.Frame(self, bg=BG_DARK, pady=20, padx=30)
        hdr.pack(fill="x")
        tk.Label(hdr, text="Booking System", font=FONT_TITLE, fg=ACCENT, bg=BG_DARK).pack(side="left")

        # Buttons bar
        bar = tk.Frame(self, bg=BG_DARK, padx=30)
        bar.pack(fill="x")
        gold_btn(bar, "➕  New Booking", self._new_booking_dialog, width=16).pack(side="left", padx=(0,10))
        gold_btn(bar, "✔  Checkout", self._checkout_dialog, width=14).pack(side="left", padx=(0,10))
        danger_btn(bar, "✖  Cancel", self._cancel_booking, width=14).pack(side="left")

        # Table
        body = tk.Frame(self, bg=BG_DARK, padx=30)
        body.pack(fill="both", expand=True, pady=16)
        section_title(body, "All Bookings").pack(fill="x", pady=(0,10))
        cols = ["ID", "Guest", "Room", "Check-In", "Check-Out", "Adults", "Children", "Status"]
        widths = [50, 150, 60, 110, 110, 60, 70, 110]
        tv_frame, self.tv = build_treeview(body, cols, widths)
        tv_frame.pack(fill="both", expand=True)

    def refresh(self):
        self.tv.delete(*self.tv.get_children())
        conn = get_conn(); cur = conn.cursor()
        cur.execute("""SELECT b.booking_id, c.name, b.room_no, b.check_in, b.check_out,
            b.adults, b.children, b.status
            FROM bookings b JOIN customers c ON b.customer_id=c.customer_id
            ORDER BY b.booking_id DESC""")
        for row in cur.fetchall():
            tag = {"Booked":"info","Checked-Out":"muted","Cancelled":"danger"}.get(row[7],"")
            self.tv.insert("", "end", values=row, tags=(tag,))
        self.tv.tag_configure("info",   background="#1A2E40")
        self.tv.tag_configure("muted",  background="#1A2535")
        self.tv.tag_configure("danger", background="#2E1A1A")
        conn.close()

    def _new_booking_dialog(self):
    
        win = tk.Toplevel(self)
        win.title("New Booking - Smart Guest Lookup")
        win.geometry("550x700")
        win.configure(bg=BG_CARD)
        win.grab_set()

        tk.Label(win, text="Room Booking", font=FONT_TITLE, fg=ACCENT, bg=BG_CARD).pack(pady=(20,10), padx=24, anchor="w")

        # --- Variables ---
        v_phone = tk.StringVar()
        v_name = tk.StringVar()
        v_country = tk.StringVar(value="India")
        v_meal = tk.StringVar(value="BB")
        
        v_room = tk.StringVar()
        v_ci = tk.StringVar(value=datetime.date.today().isoformat())
        v_co = tk.StringVar(value=(datetime.date.today() + datetime.timedelta(days=1)).isoformat())
        v_adt = tk.StringVar(value="1")
        v_ch = tk.StringVar(value="0")
        
        self.found_cust_id = None # Track if we found an existing user

        form = tk.Frame(win, bg=BG_CARD, padx=24)
        form.pack(fill="both", expand=True)

        # --- Guest Lookup Section ---
        tk.Label(form, text="Search Guest by Phone", font=FONT_BOLD, fg=ACCENT, bg=BG_CARD).pack(anchor="w", pady=(10,5))
        
        search_frame = tk.Frame(form, bg=BG_CARD)
        search_frame.pack(fill="x")
        
        ent_phone = entry(search_frame, textvariable=v_phone, width=20)
        ent_phone.pack(side="left", padx=(0,10))
        
        def lookup_guest():
            phone = v_phone.get().strip()
            if not phone:
                messagebox.showwarning("Input", "Enter phone number to search.")
                return
            
            conn = get_conn(); cur = conn.cursor()
            cur.execute("SELECT customer_id, name, country, meal_plan FROM customers WHERE phone=?", (phone,))
            res = cur.fetchone()
            conn.close()
            
            if res:
                self.found_cust_id = res[0]
                v_name.set(res[1])
                v_country.set(res[2])
                v_meal.set(res[3])
                messagebox.showinfo("Guest Found", f"Welcome back, {res[1]}!\nDetails auto-filled.")
            else:
                self.found_cust_id = None
                messagebox.showinfo("New Guest", "No record found. Please enter details for the new guest.")

        gold_btn(search_frame, "🔍 Search", lookup_guest, width=10).pack(side="left")

        # --- Guest Details (Auto-filled or Manual) ---
        for lbl, var in [("Guest Name *", v_name), ("Country", v_country)]:
            tk.Label(form, text=lbl, font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(10,2))
            entry(form, textvariable=var).pack(anchor="w", fill="x")

        # --- Room and Dates ---
        conn = get_conn(); cur = conn.cursor()
        cur.execute("SELECT room_no, room_type, price FROM rooms WHERE status='Available'")
        avail = cur.fetchall()
        conn.close()
        room_strs = [f"Room {r[0]} — {r[1]} — ₹{r[2]}/night" for r in avail]

        tk.Label(form, text="Available Room *", font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(10,2))
        cb_room = ttk.Combobox(form, values=room_strs, textvariable=v_room, width=44, font=FONT_LABEL)
        cb_room.pack(anchor="w", fill="x")
        if room_strs: cb_room.current(0)

        for lbl, var in [("Check-In (YYYY-MM-DD)", v_ci), ("Check-Out (YYYY-MM-DD)", v_co)]:
            tk.Label(form, text=lbl, font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(10,2))
            entry(form, textvariable=var).pack(anchor="w", fill="x")

        def do_smart_book():
            try:
                # 1. Validation
                name = v_name.get().strip()
                phone = v_phone.get().strip()
                room_no = int(v_room.get().split(" ")[1])
                ci, co = v_ci.get().strip(), v_co.get().strip()
                
                if not name or not phone:
                    messagebox.showerror("Error", "Name and Phone are required.")
                    return

                conn2 = get_conn(); cur2 = conn2.cursor()
                
                # 2. Handle Customer (New vs Existing)
                if self.found_cust_id is None:
                    # Create new customer if not found during search
                    cur2.execute("INSERT INTO customers (name, phone, country) VALUES (?,?,?)", 
                                 (name, phone, v_country.get()))
                    cust_id = cur2.lastrowid
                else:
                    cust_id = self.found_cust_id
                    # Optional: Update name in case they want to fix a typo
                    cur2.execute("UPDATE customers SET name=? WHERE customer_id=?", (name, cust_id))

                # 3. Create Booking
                cur2.execute("INSERT INTO bookings (customer_id,room_no,check_in,check_out,adults,children) VALUES (?,?,?,?,?,?)",
                             (cust_id, room_no, ci, co, int(v_adt.get()), int(v_ch.get())))
                cur2.execute("UPDATE rooms SET status='Occupied' WHERE room_no=?", (room_no,))
                
                conn2.commit(); conn2.close()
                messagebox.showinfo("Success", "Booking confirmed!")
                win.destroy()
                self.refresh()
                
            except Exception as e:
                messagebox.showerror("Error", f"Booking failed: {e}")

        gold_btn(form, "Confirm Booking", do_smart_book, width=22).pack(pady=20, fill="x")

        def do_book():
            try:
                room_no = int(v_room.get().split(" ")[1])
                cid     = int(v_cust.get().split(":")[0])
                ci, co  = v_ci.get().strip(), v_co.get().strip()
                adults  = int(v_adt.get() or 1)
                children= int(v_ch.get() or 0)
                datetime.date.fromisoformat(ci)
                datetime.date.fromisoformat(co)
            except Exception:
                messagebox.showerror("Error", "Please fill all fields correctly.", parent=win)
                return
            conn2 = get_conn(); cur2 = conn2.cursor()
            cur2.execute("SELECT status FROM rooms WHERE room_no=?", (room_no,))
            row = cur2.fetchone()
            if not row or row[0] != "Available":
                messagebox.showerror("Error", "Room is not available!", parent=win)
                conn2.close(); return
            cur2.execute("INSERT INTO bookings (customer_id,room_no,check_in,check_out,adults,children) VALUES (?,?,?,?,?,?)",
                         (cid, room_no, ci, co, adults, children))
            cur2.execute("UPDATE rooms SET status='Occupied' WHERE room_no=?", (room_no,))
            conn2.commit()
            bid = cur2.lastrowid
            conn2.close()
            messagebox.showinfo("Booked!", f"✓ Booking confirmed!\nBooking ID: {bid}", parent=win)
            win.destroy()
            self.refresh()

        gold_btn(form, "Confirm Booking", do_book, width=22).pack(pady=20, fill="x")
        if not avail:
            messagebox.showwarning("No Rooms", "No rooms are available right now.", parent=win)

    def _checkout_dialog(self):
        sel = self.tv.selection()
        if not sel:
            messagebox.showinfo("Select Booking", "Please select a booking to checkout.")
            return
        bid = self.tv.item(sel[0])["values"][0]
        conn = get_conn(); cur = conn.cursor()
        cur.execute("""SELECT b.booking_id, c.name, r.room_no, r.room_type, r.price,
            b.check_in, b.check_out, b.adults, b.children
            FROM bookings b JOIN customers c ON b.customer_id=c.customer_id
            JOIN rooms r ON b.room_no=r.room_no
            WHERE b.booking_id=? AND b.status='Booked'""", (bid,))
        row = cur.fetchone()
        conn.close()
        if not row:
            messagebox.showerror("Error", "Booking not found or already checked out.")
            return
        _, name, room_no, room_type, price, ci, co, adults, children = row
        nights = max((datetime.date.fromisoformat(co) - datetime.date.fromisoformat(ci)).days, 1)
        # Calculate using the tiered engine
        total = calculate_stay_price(room_type, nights)
        if messagebox.askyesno("Confirm Checkout",
            f"Guest: {name}\nRoom: {room_no} ({room_type})\n"
            f"{ci} → {co} ({nights} night(s))\nTotal: ₹{total:,.2f}\n\nConfirm checkout?"):
            conn = get_conn(); cur = conn.cursor()
            cur.execute("UPDATE bookings SET status='Checked-Out' WHERE booking_id=?", (bid,))
            cur.execute("UPDATE rooms SET status='Available' WHERE room_no=?", (room_no,))
            # Mark room as Available for future booking, but 'Dirty' for the HK staff
            cur.execute("UPDATE rooms SET status='Available', hk_status='Dirty' WHERE room_no=?", (room_no,))
            cur.execute("INSERT INTO bills (booking_id,total_amt,paid) VALUES (?,?,'Yes')", (bid, total))
            conn.commit(); conn.close()
            messagebox.showinfo("Done", f"Checkout complete.\nBill: ₹{total:,.2f} recorded.")
            self.refresh()

    def _cancel_booking(self):
        sel = self.tv.selection()
        if not sel:
            messagebox.showinfo("Select Booking", "Please select a booking to cancel.")
            return
        bid = self.tv.item(sel[0])["values"][0]
        status = self.tv.item(sel[0])["values"][7]
        if status != "Booked":
            messagebox.showerror("Error", "Only active bookings can be cancelled.")
            return
        if messagebox.askyesno("Cancel Booking", f"Cancel Booking ID {bid}?"):
            conn = get_conn(); cur = conn.cursor()
            cur.execute("SELECT room_no FROM bookings WHERE booking_id=?", (bid,))
            room_no = cur.fetchone()[0]
            cur.execute("UPDATE bookings SET status='Cancelled' WHERE booking_id=?", (bid,))
            cur.execute("UPDATE rooms SET status='Available' WHERE room_no=?", (room_no,))
            conn.commit(); conn.close()
            messagebox.showinfo("Cancelled", "Booking cancelled and room is now available.")
            self.refresh()


# ─────────────────────────────────────────
# BILLING PAGE
# ─────────────────────────────────────────

class BillingPage(tk.Frame):
    def __init__(self, parent, app):
        super().__init__(parent, bg=BG_DARK)
        self.app = app
        self._build()

    def _build(self):
        hdr = tk.Frame(self, bg=BG_DARK, pady=20, padx=30)
        hdr.pack(fill="x")
        tk.Label(hdr, text="Billing System", font=FONT_TITLE, fg=ACCENT, bg=BG_DARK).pack(side="left")

        body = tk.Frame(self, bg=BG_DARK)
        body.pack(fill="both", expand=True, padx=30)

        # Left: bills table
        left = tk.Frame(body, bg=BG_DARK)
        left.pack(side="left", fill="both", expand=True, padx=(0,20))
        section_title(left, "All Bills").pack(fill="x", pady=(0,10))
        cols = ["Bill ID", "Guest", "Booking ID", "Amount", "Paid"]
        widths = [70, 160, 90, 110, 80]
        tv_frame, self.tv = build_treeview(left, cols, widths)
        tv_frame.pack(fill="both", expand=True)

        # Right: invoice
        right = tk.Frame(body, bg=BG_CARD, width=280, padx=20, pady=20,
                         highlightthickness=1, highlightbackground=BORDER)
        right.pack(side="right", fill="y")
        right.pack_propagate(False)

        tk.Label(right, text="Generate Invoice", font=FONT_HEADER, fg=ACCENT, bg=BG_CARD).pack(anchor="w", pady=(0,14))
        self.v_bid = tk.StringVar()
        tk.Label(right, text="Booking ID", font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_CARD).pack(anchor="w", pady=(0,4))
        entry(right, textvariable=self.v_bid).pack(anchor="w", fill="x")
        gold_btn(right, "🧾 Generate Bill", self._generate_bill, width=22).pack(pady=12, fill="x")

        # Invoice display
        self.inv_frame = tk.Frame(right, bg=BG_DARK, padx=12, pady=12)
        self.inv_frame.pack(fill="both", expand=True)
        self.inv_lbl = tk.Label(self.inv_frame, text="Select a booking ID\nand generate invoice.",
                                font=FONT_SMALL, fg=TEXT_MUTED, bg=BG_DARK, justify="left")
        self.inv_lbl.pack(anchor="w")

    def refresh(self):
        self.tv.delete(*self.tv.get_children())
        conn = get_conn(); cur = conn.cursor()
        cur.execute("""SELECT bl.bill_id, c.name, bl.booking_id, bl.total_amt, bl.paid
            FROM bills bl JOIN bookings b ON bl.booking_id=b.booking_id
            JOIN customers c ON b.customer_id=c.customer_id
            ORDER BY bl.bill_id DESC""")
        for row in cur.fetchall():
            tag = "paid" if row[4] == "Yes" else "pend"
            self.tv.insert("", "end",
                           values=(row[0], row[1], row[2], f"₹{row[3]:,.2f}", row[4]),
                           tags=(tag,))
        self.tv.tag_configure("paid", background="#152218")
        self.tv.tag_configure("pend", background="#2E2A12")
        conn.close()

    def _generate_bill(self):
        try:
            bid = int(self.v_bid.get())
        except ValueError:
            messagebox.showerror("Error", "Enter a valid Booking ID.")
            return
        conn = get_conn(); cur = conn.cursor()
        cur.execute("""SELECT b.booking_id, c.name, c.phone, c.country, c.meal_plan,
            r.room_no, r.room_type, r.price, b.check_in, b.check_out,
            b.adults, b.children, b.status
            FROM bookings b JOIN customers c ON b.customer_id=c.customer_id
            JOIN rooms r ON b.room_no=r.room_no
            WHERE b.booking_id=?""", (bid,))
        row = cur.fetchone()
        if not row:
            messagebox.showerror("Not Found", f"No booking found with ID {bid}.")
            conn.close(); return
        _, name, phone, country, meal, room_no, room_type, price, ci, co, adults, children, status = row
        nights     = max((datetime.date.fromisoformat(co) - datetime.date.fromisoformat(ci)).days, 1)
        # Ensure the invoice displays the correct tiered pricing
        room_chg = calculate_stay_price(room_type, nights)
        meal_rate  = {"BB":300,"HB":600,"FB":900}.get(meal, 300)
        meal_chg   = meal_rate * nights * (adults + children)
        tax        = round((room_chg + meal_chg) * 0.12, 2)
        total      = round(room_chg + meal_chg + tax, 2)
        cur.execute("SELECT paid FROM bills WHERE booking_id=?", (bid,))
        br = cur.fetchone()
        paid_status = br[0] if br else "Pending"
        conn.close()

        lines = [
            "━━━━━━━━━━━━━━━━━━━━━━━━━━━",
            "    HOTEL INVOICE",
            "━━━━━━━━━━━━━━━━━━━━━━━━━━━",
            f"Booking ID  : {bid}",
            f"Guest       : {name}",
            f"Phone       : {phone}",
            f"Country     : {country}",
            f"Room        : {room_no} ({room_type})",
            f"Meal Plan   : {meal}",
            f"Check-in    : {ci}",
            f"Check-out   : {co}",
            f"Nights      : {nights}",
            f"Adults/Child: {adults}/{children}",
            "───────────────────────────",
            f"Room Charges: ₹{room_chg:,.2f}",
            f"Meal Charges: ₹{meal_chg:,.2f}",
            f"Tax (12%)   : ₹{tax:,.2f}",
            "───────────────────────────",
            f"TOTAL       : ₹{total:,.2f}",
            f"Status      : {paid_status}",
            "━━━━━━━━━━━━━━━━━━━━━━━━━━━",
        ]

        for w in self.inv_frame.winfo_children():
            w.destroy()
        tk.Label(self.inv_frame,
                 text="\n".join(lines),
                 font=("Courier", 9), fg=TEXT_MAIN, bg=BG_DARK,
                 justify="left", anchor="nw").pack(fill="both", expand=True)


# ─────────────────────────────────────────
# HOUSEKEEPING PAGE
# ─────────────────────────────────────────
class HousekeepingPage(tk.Frame):
    def __init__(self, parent, app):
        super().__init__(parent, bg=BG_DARK)
        self.app = app
        self._build()

    def _build(self):
        hdr = tk.Frame(self, bg=BG_DARK, pady=20, padx=30)
        hdr.pack(fill="x")
        tk.Label(hdr, text="Housekeeping Management", font=FONT_TITLE, fg=ACCENT, bg=BG_DARK).pack(side="left")

        body = tk.Frame(self, bg=BG_DARK, padx=30)
        body.pack(fill="both", expand=True)

        # Control Buttons
        btn_bar = tk.Frame(body, bg=BG_DARK)
        btn_bar.pack(fill="x", pady=(0,15))
        gold_btn(btn_bar, "✨ Mark Cleaned", lambda: self._update_hk("Clean"), width=15).pack(side="left", padx=5)
        gold_btn(btn_bar, "🧹 Mark Dirty", lambda: self._update_hk("Dirty"), width=15).pack(side="left", padx=5)
        danger_btn(btn_bar, "📞 Guest Call", lambda: self._update_hk("Service Requested"), width=15).pack(side="left", padx=5)

        # Room Status Table
        cols = ["Room No", "Type", "Occupancy", "HK Status"]
        widths = [80, 120, 120, 180]
        f, self.tv = build_treeview(body, cols, widths)
        f.pack(fill="both", expand=True)

    def refresh(self):
        self.tv.delete(*self.tv.get_children())
        conn = get_conn(); cur = conn.cursor()
        cur.execute("SELECT room_no, room_type, status, hk_status FROM rooms")
        for row in cur.fetchall():
            # Color coding based on status
            tag = "dirty" if row[3] == "Dirty" else "clean"
            if row[3] == "Service Requested": tag = "request"
            self.tv.insert("", "end", values=row, tags=(tag,))
        
        self.tv.tag_configure("dirty", background="#2E1A1A") 
        self.tv.tag_configure("clean", background="#152218") 
        self.tv.tag_configure("request", background="#2E2A12") 
        conn.close()

    def _update_hk(self, new_status):
        sel = self.tv.selection()
        if not sel:
            messagebox.showinfo("Selection", "Please select a room first.")
            return
        room_no = self.tv.item(sel[0])['values'][0]
        conn = get_conn(); cur = conn.cursor()
        cur.execute("UPDATE rooms SET hk_status=? WHERE room_no=?", (new_status, room_no))
        conn.commit(); conn.close()
        self.refresh()
# ─────────────────────────────────────────
# ENTRY POINT
# ─────────────────────────────────────────

if __name__ == "__main__":
    app = HotelApp()
    app.mainloop()
