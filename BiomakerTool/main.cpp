#include "BiomakerTool.h"
#include <QtWidgets/QApplication>
#include "CaptureGraphicsItem.h"
#include <QDir>
QVector<QRect> CaptureGraphicsItem::captureRects = QVector<QRect>();
int CaptureGraphicsItem::loadedNum = 0;
int main(int argc, char *argv[])
{


	QApplication a(argc, argv);
	BiomakerTool w;

	//w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint);
	w.showMaximized();
	//w.setFixedSize(w.size());
	//w.setWindowFlags(Qt::Window);
	//w.showMaximized();
	//w.setFixedSize(w.size());
	//w.layout()->setSizeConstraint(QLayout::SetFixedSize);
	w.setWindowTitle("Biomark Tool");
	w.setWindowIcon(QIcon("icon.bmp"));
	QDir dir;
	if (!dir.exists("./workspace"))
	{
		bool res = dir.mkpath("./workspace");
	}

	w.show();
	return a.exec();
}
