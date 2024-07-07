-- SQL script to create tables
CREATE TABLE IF NOT EXISTS stocks (
    stock_id INTEGER PRIMARY KEY AUTOINCREMENT,
    symbol TEXT NOT NULL UNIQUE,
    company_name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS portfolio (
    portfolio_id INTEGER PRIMARY KEY AUTOINCREMENT,
    stock_id INTEGER,
    quantity INTEGER,
    average_price DECIMAL(10, 2),
    FOREIGN KEY (stock_id) REFERENCES stocks(stock_id)
);

CREATE TABLE IF NOT EXISTS transactions (
    transaction_id INTEGER PRIMARY KEY,
    stock_id INTEGER,
    price DECIMAL(10,2),
    quantity INTEGER NOT NULL,
    transaction_type TEXT CHECK (transaction_type IN ('BUY', 'SELL')),
    transaction_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (stock_id) REFERENCES stocks(stock_id)
);