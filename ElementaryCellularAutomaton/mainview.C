/*
  Elementary cellular automaton.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <mainview.H>

# include <QMessageBox>
# include <QValidator>

MainView::MainView(QWidget * parent)
  : QWidget(parent), running(false)
{
  setWindowTitle("Elementary Cellular Automaton");
  init_gui();
}

void MainView::init_gui()
{
  QVBoxLayout * main_layout = new QVBoxLayout;
  setLayout(main_layout);

  QHBoxLayout * hlayout = new QHBoxLayout;

  hlayout->addStretch();
  lbl_rule = new QLabel("Rule", this);
  hlayout->addWidget(lbl_rule);
  edt_rule = new QLineEdit(this);
  edt_rule->setValidator(new QIntValidator);
  hlayout->addWidget(edt_rule);
  btn_run = new QPushButton("Run", this);
  hlayout->addWidget(btn_run);
  btn_clear = new QPushButton("Clear", this);
  hlayout->addWidget(btn_clear);
  hlayout->addStretch();

  main_layout->addLayout(hlayout);

  automaton_panel = new AutomatonPanel(this);

  main_layout->addWidget(automaton_panel);

  connect(btn_run, SIGNAL(clicked(bool)), this, SLOT(slot_run()));
  connect(btn_clear, SIGNAL(clicked(bool)), this, SLOT(slot_clear()));
}

void MainView::slot_run()
{
  if (running)
    {
      automaton_panel->stop();
      btn_run->setText("Run");
      btn_clear->setEnabled(true);
      running = false;
    }
  else
    {
      if (edt_rule->text().isEmpty())
        {
          QMessageBox::critical(this, "Error", "Write a number of rule");
          return;
        }

      int rule = edt_rule->text().toInt();

      automaton_panel->run(rule);
      btn_run->setText("Stop");
      btn_clear->setEnabled(false);
      running = true;
      edt_rule->setEnabled(false);
    }
}

void MainView::slot_clear()
{
  automaton_panel->clear();
  edt_rule->setEnabled(true);
}
