import sys
from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QLabel,
    QLineEdit,
    QVBoxLayout,
    QHBoxLayout,
    QHeaderView,
    QWidget,
    QTableWidget,
    QTableWidgetItem,
    QMessageBox,
    QLineEdit,
    QSizePolicy, 
    QSpacerItem,
)

class MyWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Financial Portfolio")
        self.setFixedWidth(700)
        self.setFixedHeight(350)

        self.main_widget = QWidget()
        self.setStyleSheet("""
            QWidget#main_widget {
                background: qlineargradient(
                    spread: pad, 
                    x1: 0, y1: 0, x2: 1, y2: 1, 
                    stop: 0 #212121,
                    stop: 1 #545454
                );
            }
        """)
        self.main_widget.setObjectName("main_widget")
        
        # Main Layout
        self.main_layout = QVBoxLayout()
        self.add_title()

        # widget Layout
        self.widget_layout = QHBoxLayout()
        ### Left column
        self.left_column = QVBoxLayout()
        self.add_portfolio_table()
        spacer_left = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
        self.left_column.addItem(spacer_left)
        ### Right column
        self.right_column = QVBoxLayout()
        self.add_search_bar()
        self.add_watchlist_table()
        spacer_right = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
        self.right_column.addItem(spacer_right)

        # Set layout of the widget layout
        self.widget_layout.addLayout(self.left_column)
        self.widget_layout.addLayout(self.right_column)
        self.widget_layout.setStretch(0, 60)  # Left column stretch factor
        self.widget_layout.setStretch(1, 40)  # Right column stretch factor
        self.main_layout.addLayout(self.widget_layout)

        # Set layout for the main widget
        self.main_widget.setLayout(self.main_layout)

        # Set layout for the main window
        layout = QVBoxLayout()
        layout.setContentsMargins(0, 0, 0, 0)  # Remove margins
        # layout.setSpacing(0)  # Remove spacing
        layout.addWidget(self.main_widget)
        self.setLayout(layout)

    def add_title(self):
        """Add main title to the main widget"""

        # Title
        title = QLabel("Financial Portfolio")
        title.setStyleSheet("""
            QLabel {
                color: white;  /* White text */
                font-size: 30px;
                font-weight: bold;
                font-family: 'Arial', sans-serif;
                padding: 10px;
                background: qlineargradient(
                    spread: pad, 
                    x1: 0, y1: 0, x2: 1, y2: 1, 
                    stop: 0 #15a0eb,
                    stop: 0.6 #186894
                );
                border-radius: 15px;  /* Rounded corners */
                border: 3px solid #212121;  /* Orange border */
            }
        """)
        self.main_layout.addWidget(title, alignment=Qt.AlignmentFlag.AlignCenter)
        
    def add_portfolio_table(self):
        """Create a portfolio table"""
        
        # Show balance
        balance_layout = QHBoxLayout()
        balanceTotal = QLabel("Balance: $1,420.69")
        balanceTotal.setStyleSheet("color: white; font-size: 18px;")
        balance_layout.addWidget(balanceTotal)
        # Show balance percentage
        balancePercentage = QLabel("+420%")
        balancePercentage.setStyleSheet("color: lightgreen; font-size: 18px;")
        balance_layout.addWidget(balancePercentage)

        # Set up table
        self.left_column.addLayout(balance_layout)
        portfolioTable = QTableWidget()
        column = ["Name", "Qty", "Buy Price", "Curr Price"]
        portfolioTable.setColumnCount(len(column))
        portfolioTable.setHorizontalHeaderLabels(column)
        portfolioTable.setRowCount(5)

        # Add data to the table
        portfolioTable.setItem(0, 0, QTableWidgetItem("TSLA"))
        portfolioTable.setItem(0, 1, QTableWidgetItem("15"))
        portfolioTable.setItem(0, 2, QTableWidgetItem("$230.78"))
        portfolioTable.setItem(0, 3, QTableWidgetItem("$471.41"))
        portfolioTable.setItem(1, 0, QTableWidgetItem("NVDA"))
        portfolioTable.setItem(1, 1, QTableWidgetItem("3"))
        portfolioTable.setItem(1, 2, QTableWidgetItem("$69.69"))
        portfolioTable.setItem(1, 3, QTableWidgetItem("$730.20"))

        # Set styles
        portfolioTable.setFixedHeight(200)
        portfolioTable.setStyleSheet("""
            QHeaderView::section {
                background: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #15a0eb,
                    stop: 1 #186894
                );
                color: white;
                font-weight: bold;
                font-size: 14px;
                border: 1px solid #212121;
                padding: 3px;
            }
            QTableWidget::item {
                background: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #f7f7f7,
                    stop: 1 #d6d6d6
                );
                color: #212121;
                font-size: 12px;
                padding: 3px;
            }
        """)
        portfolioTable.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeMode.Stretch)  # Name column stretches
        portfolioTable.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeMode.Fixed)  # Qty column stays fixed
        portfolioTable.horizontalHeader().setSectionResizeMode(2, QHeaderView.ResizeMode.Stretch)  # Buy Price column stretches
        portfolioTable.horizontalHeader().setSectionResizeMode(3, QHeaderView.ResizeMode.Stretch)  # Curr Price column stretches
        portfolioTable.setDisabled(True)
        
        # Add widget
        self.left_column.addWidget(portfolioTable)

    def add_search_bar(self):
        """Stock search bar"""

        search = QLabel("Search for a stock")
        search.setStyleSheet("color: white; font-size: 18px;")
        self.right_column.addWidget(search)
        searchbar = QLineEdit("Enter stock name...")

        # Set styles
        searchbar.setStyleSheet("""
            QLineEdit {
                border: 1px solid #212121;
                border-radius: 10px;
                padding: 3px;
                background: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #15a0eb,
                    stop: 1 #186894
                );
                font-size: 12px;
                font-weight: bold;
                color: white;
                            
            }
            
            QLineEdit:hover {
                font-weight: bold;
                background: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #186894,    /* light blue */
                    stop: 1 #15a0eb     /* dark blue */
                );
            }
        """)

        # Add widget
        self.right_column.addWidget(searchbar)

    def add_watchlist_table(self):
        """Create a watchlist table"""

        watchlist = QLabel("Watchlist")
        watchlist.setStyleSheet("color: white; font-size: 18px;")
        self.right_column.addWidget(watchlist)
        watchListTable = QTableWidget(3, 2)
        watchListTable.setHorizontalHeaderLabels(["Stock", "Price"])
        watchListTable.setItem(0, 0, QTableWidgetItem("TSLA"))
        watchListTable.setItem(0, 1, QTableWidgetItem("$420.69"))
        watchListTable.setItem(1, 0, QTableWidgetItem("NVDA"))
        watchListTable.setItem(1, 1, QTableWidgetItem("$730.20"))

        # Set styles
        watchListTable.setFixedHeight(143)
        watchListTable.setStyleSheet("""
            QHeaderView::section {
                background: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #15a0eb,
                    stop: 1 #186894
                );
                color: white;
                font-weight: bold;
                font-size: 14px;
                border: 1px solid #212121;
                padding: 3px;
            }
            QTableWidget::item {
                background: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #f7f7f7,
                    stop: 1 #d6d6d6
                );
                color: #212121;
                font-size: 12px;
                border: 0px;
                padding: 3px;
            }
        """)
        watchListTable.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeMode.Stretch)  # Stock column stretches
        watchListTable.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)  # Price column stretches
        watchListTable.setDisabled(True)

        # Add widget
        self.right_column.addWidget(watchListTable)

if __name__ == "__main__":
    # Create the QApplication object
    app = QApplication(sys.argv)

    # Create an instance of MyWindow
    window = MyWindow()

    # Show the window
    window.show()

    # Start the event loop
    sys.exit(app.exec())