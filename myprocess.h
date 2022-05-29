#include <QtCore>
class MyProcess : public QObject {
   Q_OBJECT
   QProcess myprocess;
   QString output;

public:
   MyProcess() : QObject() {
      myprocess.start("./calculator");

      // probably nothing here yet
      qDebug() << "Output right after start:"
               << myprocess.readAllStandardOutput();

      // get informed when data is ready
      connect(&myprocess, SIGNAL(readyReadStandardOutput()),
              this, SLOT(readSubProcess()));
   };

private slots:
   // here we check what was received (called everytime new data is readable)
   void readSubProcess(void) {
      output.append(myprocess.readAllStandardOutput());
      qDebug() << "complete output: " << output;

      // check if input is expected
      if (output.endsWith("type\n")) {
         qDebug() << "ready to receive input";

         // write something to subprocess, if the user has provided input,
         // you need to (read it and) forward it here.
         myprocess.write("hallo back!\n");
         // reset outputbuffer
         output = "";
      }

      // subprocess indicates it finished
      if (output.endsWith("Bye!\n")) {
         // wait for subprocess and exit
         myprocess.waitForFinished();
         QCoreApplication::exit();
      }
   };
};

