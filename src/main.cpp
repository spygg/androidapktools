#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
#include <QIcon>
#include <QDebug>

void copyFiles(QString srcPath, QString desPath)
{
    QDir dir(desPath);
    QDir dirSrc(srcPath);

    if(!dir.exists()){
        dir.mkpath(desPath);
    }

    foreach( QFileInfo fi, dirSrc.entryInfoList()){
        if(fi.isFile()){
            QString desFilepath = QString("%1/%2").arg(desPath, fi.fileName());

            if(!QFile::exists(desFilepath)){
                QFile::copy(fi.filePath(), desFilepath);
                QFile::setPermissions(desFilepath, QFileDevice::ReadOwner | QFileDevice::WriteOwner);
            }
        }
        else{
            if(fi.fileName() == "." || fi.fileName() == "..")
                continue;
            copyFiles(fi.filePath(), QString("%1/%2").arg(desPath, fi.fileName()));
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/apk.png"));

    QString currentPath = QCoreApplication::applicationDirPath();

    //先拷贝必要的资源到制定路径
    QString scripts = QString("%1/").arg(currentPath);
    copyFiles(":/res/", scripts);

    QString jdguiPath = QString("%1/jd-gui.exe").arg(currentPath);

    if(argc <= 1){
        qDebug() << "useage: apktool XXX.apk";

        QProcess::startDetached(jdguiPath, QStringList());
        return -1;
    }
    //E:\programes\apk\dex-tools-2.2\d2j-dex2jar.bat %1


    QString dexToolPath = QString("%1/dex-tools-2.2/d2j-dex2jar.bat").arg(currentPath);

    QFileInfo fi(argv[1]);

    if(!fi.exists()){
        qDebug() << "apk文件路径错误啊!";
        return -1;
    }

    //第一步生成jar文件
    QStringList params;
    for(int i = 1; i < argc; i++){
        params << QString("%1").arg(argv[i]);
    }
    params << "2>&1";

    QProcess p;
    p.start(dexToolPath, params);
    p.waitForStarted();
    p.waitForFinished();

    QByteArray output = p.readAllStandardOutput();
    qDebug().noquote()  << QString::fromLocal8Bit(output);

    //第二步调用jd-gui
   if(output.indexOf("Exception") == -1){



        qDebug() << fi.absolutePath() << fi.fileName() << fi.baseName();
        //-dex2jar.jar

        QString jarPath = QString("%1/%2-dex2jar.jar").arg(fi.absolutePath()).arg(fi.baseName());
        QProcess::startDetached(jdguiPath, QStringList(jarPath));
    }



    a.exit(0);
}
