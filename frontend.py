# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'frontend.ui'
#
# Created by: PyQt4 UI code generator 4.12.1
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(650, 421)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.submit = QtGui.QPushButton(self.centralwidget)
        self.submit.setGeometry(QtCore.QRect(230, 310, 181, 41))
        self.submit.setStyleSheet(_fromUtf8("background-color: rgb(170, 0, 0);\n"
"font: 75 14pt \"Ubuntu\";"))
        self.submit.setObjectName(_fromUtf8("submit"))
        self.label = QtGui.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(160, 140, 131, 51))
        self.label.setStyleSheet(_fromUtf8("font: 75 12pt \"Ubuntu\";"))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_2 = QtGui.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(160, 190, 131, 51))
        self.label_2.setStyleSheet(_fromUtf8("font: 75 12pt \"Ubuntu\";"))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.label_3 = QtGui.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(230, 40, 261, 61))
        self.label_3.setStyleSheet(_fromUtf8("font: italic 20pt \"Ubuntu\";"))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.src_ip = QtGui.QLineEdit(self.centralwidget)
        self.src_ip.setGeometry(QtCore.QRect(300, 150, 191, 41))
        self.src_ip.setObjectName(_fromUtf8("src_ip"))
        self.dest_ip = QtGui.QLineEdit(self.centralwidget)
        self.dest_ip.setGeometry(QtCore.QRect(300, 200, 191, 41))
        self.dest_ip.setObjectName(_fromUtf8("dest_ip"))
        self.label_4 = QtGui.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(160, 250, 131, 41))
        self.label_4.setStyleSheet(_fromUtf8("font: 75 12pt \"Ubuntu\";"))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.payload = QtGui.QLineEdit(self.centralwidget)
        self.payload.setGeometry(QtCore.QRect(300, 250, 191, 41))
        self.payload.setObjectName(_fromUtf8("payload"))
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 650, 25))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        self.submit.clicked.connect(self.Attack)
	
    def Attack(self):
        victim_ip = str(self.src_ip.text())
        server_ip = str(self.dest_ip.text())
        payload = str(self.payload.text())
        print("Attacked ->" + victim_ip + " " + server_ip)
        print("Payload  ->" + payload)
        # import subprocess
        # subprocess.run(["icmpping", "1.2.3.4", "8.8.8.8"])
        cmd = "./spoof.sh \"" + victim_ip + "\" \"" + server_ip + "\"" + " \"" + payload + "\" ; exec bash"
        # cmd = "./spoof.sh \"" + victim_ip + "\" \"" + server_ip + "\"" + " \"" + payload + "\""
        import os
        # os.system("bash ./spoof.sh \"" + victim_ip + "\" \"" + server_ip + "\"" + " \"" + payload + "\"")
        cmdline = 'gnome-terminal -e \'bash -c  "'+cmd+'"\''
        print(cmdline)
        os.system(cmdline)
        # os.system(cmd)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "Ping Spoofing", None))
        self.submit.setText(_translate("MainWindow", "Send Spoofed Ping", None))
        self.label.setText(_translate("MainWindow", "Victim\'s Address: ", None))
        self.label_2.setText(_translate("MainWindow", "Server Address:", None))
        self.label_3.setText(_translate("MainWindow", "ICMP Ping Spoofing", None))
        self.label_4.setText(_translate("MainWindow", "Payload", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    MainWindow = QtGui.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

