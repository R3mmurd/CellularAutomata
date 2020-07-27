/*
  Elementary cellular automaton.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QApplication>
# include <mainview.H>

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  MainView view;
  view.show();
  return app.exec();
}
