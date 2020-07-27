/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QApplication>

# include <mainpanel.H>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainPanel p;
  p.show();

  return app.exec();
}

