#include "buttonstyles.h"

const QString defaultButtonStyle = R"(
    QPushButton {
        font-family: 'Roboto Condensed', sans-serif;
        font-size: 45px;
        color: white;
        background-color: transparent;
        border: none;
    }
    QPushButton:hover {
        color: #330C24;
    }
)";

const QString activeButtonStyle = R"(
    QPushButton {
        font-family: 'Roboto Condensed', sans-serif;
        font-size: 45px;
        color: #330C24;
        background-color: transparent;
        border: none;
    }
)";
