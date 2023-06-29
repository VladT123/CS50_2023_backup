import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # user_id used to specify specific user.
    user_id = session["user_id"]
    # Trans_act (short of transaction) is aditioanal Database it keeps record of every bought share and which user it belong too.
    transactions = db.execute("SELECT Name, Symbol, count(*)  AS c, cost FROM Trans_act WHERE User_ID=? GROUP BY Symbol", user_id)
    users = db.execute("SELECT * FROM users WHERE id=?", user_id)
    # Extracts every type of share that uses own
    symbols = db.execute("SELECT DISTINCT Symbol FROM Trans_act WHERE User_ID=? GROUP BY Symbol", user_id)
    # Creates a list with up to date prices for shares
    list_1 = list()
    for x in range(len(symbols)):
        s = symbols[x]
        current_symbol = list(s.values())[0]
        symbol = lookup(current_symbol)
        c = symbol.get('price')
        list_1.append(c)

    return render_template("index.html", users=users, transactions=transactions, list_1=list_1, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        user_id = session["user_id"]
        req = request.form.get("symbol")
        try:
            amt = int(request.form.get("shares"))
        except:
            return apology("Something went wrong")
        if amt <= -1 or isinstance(amt, int) is False:
            return apology("Cant buy negative shares")
        symbol = lookup(req)
        if symbol is None:
            return apology("Share not found")
        c = db.execute("SELECT cash FROM users WHERE id=?", user_id)
        # Used to extract specific values from db
        s = c[0]
        current_cash = list(s.values())[0]
        price = symbol.get('price')
        if current_cash < price*amt:
            return apology("Cant afford")
        new_cash = current_cash-price*amt
        db.execute("UPDATE users SET cash = ? WHERE id=?", new_cash, user_id)
        for x in range(amt):
            db.execute("INSERT INTO Trans_act (Symbol, Name, User_ID, cost) VALUES(?, ?, ?, ?)",
                       req.upper(), symbol.get('name'), user_id, price)
        db.execute("INSERT INTO Archive (Symbol, Name, User_ID, cost, Type, Amount) VALUES(?, ?, ?, ?, ?, ?)",
                   req.upper(), symbol.get('name'), user_id, price, 'Bought', amt)
        users = db.execute("SELECT * FROM users WHERE id=?", user_id)
        return render_template("purchase_info.html", symbol=symbol, usd=usd, users=users, amt=amt, msg='bought')
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]
    # Archive db mostly mirrors transactions db but also keep track of sold shares.
    archive = db.execute("SELECT * FROM Archive WHERE User_ID=?", user_id)
    users = db.execute("SELECT * FROM users WHERE id=?", user_id)
    return render_template("archive.html", users=users, archive=archive, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        req = request.form.get("symbol")
        symbol = lookup(req)
        if symbol is None:
            return apology("Share not found")
        return render_template("stock_info.html", symbol=symbol, usd=usd)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        password = request.form.get("password")
        if password == '':
            return apology("Password empty")
        confrimation = request.form.get("confirmation")
        if confrimation == '':
            return apology("Confrimation empty")
        if password != confrimation:
            return apology("Paswords dont match")
        h_password = generate_password_hash(password)
        login = request.form.get("username")
        if login == '':
            return apology("Username empty")
        check = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(check) != 0:
            return apology("taken")
        else:
            pass
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", login, h_password)
        return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        user_id = session["user_id"]
        try:
            amt = int(request.form.get("shares"))
        except:
            return apology("Something went wrong")
        if amt <= -1 or isinstance(amt, int) is False:
            return apology("Cant sell negative shares")
        req = request.form.get("symbol")
        transactions = db.execute(
            "SELECT Symbol, count(*)  AS c, cost FROM Trans_act WHERE User_ID=? and Symbol =? GROUP BY symbol", user_id, req)
        t = transactions[0]
        current_shares = list(t.values())[1]
        if amt > current_shares:
            return apology("not enough shares")
        symbol = lookup(req)
        c = db.execute("SELECT cash FROM users WHERE id=?", user_id)
        s = c[0]
        current_cash = list(s.values())[0]
        price = symbol.get('price')
        new_cash = current_cash+price*amt
        db.execute("UPDATE users SET cash = ? WHERE id=?", new_cash, user_id)
        db.execute("DELETE FROM Trans_act WHERE User_ID=? and Symbol=? LIMIT ?", user_id, req, amt)
        db.execute("INSERT INTO Archive (Symbol, Name, User_ID, cost, Type, Amount) VALUES(?, ?, ?, ?, ?, ?)",
                   req, symbol.get('name'), user_id, price, 'Sold', amt)
        users = db.execute("SELECT * FROM users WHERE id=?", user_id)
        return render_template("purchase_info.html", symbol=symbol, usd=usd, users=users, amt=amt, msg='sold')
    else:
        user_id = session["user_id"]
        stocks = db.execute("SELECT Symbol FROM Trans_act WHERE User_ID=? GROUP BY Symbol", user_id)
        return render_template("sell.html", stocks=stocks)


# This route used to update password of logged in user. In order to update password user need to enter their existing password.
@app.route("/user_page", methods=["GET", "POST"])
@login_required
def user_page():
    if request.method == "POST":
        user_id = session["user_id"]
        users = db.execute("SELECT * FROM users WHERE id=?", user_id)
        old_pass = request.form.get("old_password")
        if old_pass == '':
            return apology("Password empty")
        old_confrimation = request.form.get("old_confirmation")
        if old_confrimation == '':
            return apology("Confrimation empty")
        if old_pass != old_confrimation:
            return apology("Paswords dont match")
        if not check_password_hash(users[0]["hash"], request.form.get("old_password")):
            return apology("invalid  password", 403)
        # New password generation
        password = request.form.get("password")
        if password == '':
            return apology("Password empty")
        confrimation = request.form.get("confirmation")
        if confrimation == '':
            return apology("Confrimation empty")
        if password != confrimation:
            return apology("Paswords dont match")
        h_password = generate_password_hash(password)
        db.execute("UPDATE users SET hash = ? WHERE id=?", h_password, user_id)
        return render_template("user_page.html", usd=usd, users=users)
    else:
        user_id = session["user_id"]
        users = db.execute("SELECT * FROM users WHERE id=?", user_id)
        return render_template("user_page.html", usd=usd, users=users)


# This route used to add aditional founds, to user
@app.route("/add_founds", methods=["GET", "POST"])
@login_required
def add():
    if request.method == "POST":
        user_id = session["user_id"]
        try:
            amt = int(request.form.get("amt"))
        except:
            return apology("Something went wrong")
        c = db.execute("SELECT cash FROM users WHERE id=?", user_id)
        s = c[0]
        current_cash = list(s.values())[0]
        new_cash = current_cash+amt
        db.execute("UPDATE users SET cash = ? WHERE id=?", new_cash, user_id)
        return redirect("/user_page")
    else:
        return redirect("/user_page")