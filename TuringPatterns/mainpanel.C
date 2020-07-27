/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QMessageBox>
# include <QToolTip>
# include <QDoubleValidator>
# include <QIntValidator>
# include <mainpanel.H>

void MainPanel::init_gui()
{
  main_layout = new QVBoxLayout;

  input_layout = new QHBoxLayout;

  lbl_p_c = new QLabel("p<sub>c</sub>", this);
  lbl_p_d = new QLabel("p<sub>d</sub>", this);
  lbl_m_a = new QLabel("m<sub>a</sub>", this);
  lbl_m_i = new QLabel("m<sub>i</sub>", this);

  edt_p_c = new QLineEdit(this);
  edt_p_d = new QLineEdit(this);
  edt_m_a = new QLineEdit(this);
  edt_m_i = new QLineEdit(this);

  btn_action = new QPushButton("Ejecutar", this);

  edt_p_c->setMaximumWidth(80);
  edt_p_d->setMaximumWidth(80);
  edt_m_a->setMaximumWidth(80);
  edt_m_i->setMaximumWidth(80);

  edt_p_c->setValidator(new QDoubleValidator);
  edt_p_d->setValidator(new QDoubleValidator);
  edt_m_a->setValidator(new QIntValidator);
  edt_m_i->setValidator(new QIntValidator);

  panel = new AutomatonPanel(automaton, this);

  input_layout->addWidget(lbl_p_c);
  input_layout->addWidget(edt_p_c);
  input_layout->addWidget(lbl_p_d);
  input_layout->addWidget(edt_p_d);
  input_layout->addWidget(lbl_m_a);
  input_layout->addWidget(edt_m_a);
  input_layout->addWidget(lbl_m_i);
  input_layout->addWidget(edt_m_i);
  input_layout->addStretch();
  input_layout->addWidget(btn_action);

  main_layout->addLayout(input_layout);
  main_layout->addWidget(panel);

  setLayout(main_layout);
}

bool MainPanel::validate()
{
  bool validated = true;

  if (edt_m_i->text().isEmpty())
    {
      validated = false;
      edt_m_i->setFocus();
    }

  if (edt_m_a->text().isEmpty())
    {
      validated = false;
      edt_m_a->setFocus();
    }

  if (edt_p_d->text().isEmpty())
    {
      validated = false;
      edt_p_d->setFocus();
    }

  if (edt_p_c->text().isEmpty())
    {
      validated = false;
      edt_p_c->setFocus();
    }

  return validated;
}

void MainPanel::update_inputs()
{
  edt_p_c->setEnabled(not running);
  edt_p_d->setEnabled(not running);
  edt_m_a->setEnabled(not running);
  edt_m_i->setEnabled(not running);

  if (running)
    btn_action->setText("Stop");
  else
    btn_action->setText("Run");
}

MainPanel::MainPanel(QWidget * parent)
  : QWidget(parent), running(false)
{
  setMaximumWidth(500);
  init_gui();
  timer.setInterval(100);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update_automaton()));
  connect(btn_action, SIGNAL(clicked()), this, SLOT(slot_btn_action_clicked()));
}

void MainPanel::slot_btn_action_clicked()
{
  if (not running)
    {
      if (not validate())
        {
          QMessageBox::critical(this, "Error", "You must fill all fields");
          return;
        }

      automaton.set_p_c(edt_p_c->text().toDouble());
      automaton.set_p_d(edt_p_d->text().toDouble());
      automaton.set_m_a(edt_m_a->text().toInt());
      automaton.set_m_i(edt_m_i->text().toInt());
      automaton.randomize();

      timer.start();
      running = true;
    }
  else
    {
      timer.stop();
      running = false;
    }

  update_inputs();
}

void MainPanel::update_automaton()
{
  automaton.update();
  panel->repaint();
}
