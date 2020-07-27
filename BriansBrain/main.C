/*
  Cellular automaton: Brian's Brain.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QApplication>
# include <automatonpanel.H>

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);

  AutomatonPanel p;
  p.show();

  return app.exec();
}
