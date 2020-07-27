/*
  Cellular automata library.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <iostream>

# include <neighborhood.H>

int main()
{
  cout << "One dimensional automaton\n"
       << "=========================\n";

  Lattice<int> lat1(ArrayDim({9}));
  
   for (size_t i = 0; i < lat1.size(0); ++i)
    {
      lat1({i}) = i + 1;
      cout << lat1({i}) << ' ';
    }

  cout << "\n\n";
  
  cout << "Neighborhood with periodic boundary condition\n"
       << "=============================================\n";
  
  for (size_t i = 0; i < lat1.size(0); ++i)
    {
      vector<int *> n = OneDimNeighborhood<int>::get_instance().
	get_neighbors(lat1, Periodic<int>::get_ptr_instance(), {i});
  
      cout << "Cell: " << lat1({i}) << "; left neighbor: "
	   << *n.at(0) << "; right neighbor: " << *n.at(1) << endl;
    }

  cout << endl;

  cout << "Neighborhood with reflect boundary condition\n"
       << "============================================\n";
  
  for (size_t i = 0; i < lat1.size(0); ++i)
    {
      vector<int *> n = OneDimNeighborhood<int>::get_instance().
	get_neighbors(lat1, Reflect<int>::get_ptr_instance(), {i});
  
      cout << "Cell: " << lat1({i}) << "; left neighbor: "
	   << *n.at(0) << "; right neighbor: " << *n.at(1) << endl;
    }

  cout << endl;
    
  cout << "Two dimensional automaton\n"
       << "=========================\n";

  Lattice<int> lat2({3, 3});
  
  int n = 1;

  for (size_t i = 0; i < lat2.size(0); ++i)
     {
       for (size_t j = 0; j < lat2.size(1); ++j)
	 {
	   lat2({i, j}) = n++;
	   cout << lat2({i, j}) << ' ';
	 }

       cout << endl;
     }

  cout << endl;
  
  cout << "Neighborhoods with periodic boundary condition\n"
       << "==============================================\n";

  for (size_t i = 0; i < lat2.size(0); ++i)
    for (size_t j = 0; j < lat2.size(1); ++j)
      {
	vector<int *> vnn = VonNeumannNeighborhood<int>::get_instance().
	  get_neighbors(lat2, Periodic<int>::get_ptr_instance(), {i, j});
	vector<int *> mn = MooreNeighborhood<int>::get_instance().
	  get_neighbors(lat2, Periodic<int>::get_ptr_instance(), {i, j});

	cout << "Cell: " << lat2({i, j}) << "; VN neighbors: { ";

	for (auto p : vnn)
	  cout << *p << ' ';
	
	cout << "}; Moore neighbors { ";

	for (auto p : mn)
	  cout << *p << ' ';

	cout << "} " << endl;
      }

  cout << endl;

  cout << "Neighborhoods with reflect boundary condition\n"
       << "=============================================\n";

  for (size_t i = 0; i < lat2.size(0); ++i)
    for (size_t j = 0; j < lat2.size(1); ++j)
      {
	vector<int *> vnn = VonNeumannNeighborhood<int>::get_instance().
	  get_neighbors(lat2, Reflect<int>::get_ptr_instance(), {i, j});
	vector<int *> mn = MooreNeighborhood<int>::get_instance().
	  get_neighbors(lat2, Reflect<int>::get_ptr_instance(), {i, j});

	cout << "Cell: " << lat2({i, j}) << "; VN neighbors: { ";

	for (auto p : vnn)
	  cout << *p << ' ';
	
	cout << "}; Moore neighbors { ";

	for (auto p : mn)
	  cout << *p << ' ';

	cout << "} " << endl;
      }

  cout << endl;
  
  cout << "Three dimensional automaton\n"
       << "===========================\n";

  Lattice<int> lat3({3, 3, 3});
  
  n = 1;

   for (size_t i = 0; i < lat3.size(0); ++i)
     for (size_t j = 0; j < lat3.size(1); ++j)
       for (size_t k = 0; k < lat3.size(2); ++k)
	 lat3({i, j, k}) = n++;

  cout << endl;

  cout << "Neighborhoods with periodic boundary condition\n"
       << "==============================================\n";
  
  for (size_t i = 0; i < lat3.size(0); ++i)
    for (size_t j = 0; j < lat3.size(1); ++j)
      for (size_t k = 0; k < lat3.size(2); ++k)
	{
	  vector<int *> vnn = VonNeumannNeighborhood<int>::get_instance().
	    get_neighbors(lat3, Periodic<int>::get_ptr_instance(), {i, j, k});
	  vector<int *> mn = MooreNeighborhood<int>::get_instance().
	    get_neighbors(lat3, Periodic<int>::get_ptr_instance(), {i, j, k});
	  assert(mn.size() == 26);
	  
	  cout << "Cell: " << lat3({i, j, k}) << "; VN neighbors: { ";
	  
	  for (auto p : vnn)
	    cout << *p << ' ';
	  
	  cout << "}; Moore neighbors { ";
	  
	  for (auto p : mn)
	    cout << *p << ' ';
	  
	  cout << "} " << endl;
	}
  
  cout << endl;

  cout << "Neighborhoods with reflect boundary condition\n"
       << "=============================================\n";
  
  for (size_t i = 0; i < lat3.size(0); ++i)
    for (size_t j = 0; j < lat3.size(1); ++j)
      for (size_t k = 0; k < lat3.size(2); ++k)
	{
	  vector<int *> vnn = VonNeumannNeighborhood<int>::get_instance().
	    get_neighbors(lat3, Reflect<int>::get_ptr_instance(), {i, j, k});
	  vector<int *> mn = MooreNeighborhood<int>::get_instance().
	    get_neighbors(lat3, Reflect<int>::get_ptr_instance(), {i, j, k});
	  assert(mn.size() == 26);
	  
	  cout << "Cell: " << lat3({i, j, k}) << "; VN neighbors: { ";
	  
	  for (auto p : vnn)
	    cout << *p << ' ';
	  
	  cout << "}; Moore neighbors { ";
	  
	  for (auto p : mn)
	    cout << *p << ' ';
	  
	  cout << "} " << endl;
	}
  
  cout << endl;
  
  cout << "Four dimensional automaton\n"
       << "==========================\n";

  Lattice<int> lat4({3, 3, 3, 3});
  
  n = 1;

   for (size_t i = 0; i < lat4.size(0); ++i)
     for (size_t j = 0; j < lat4.size(1); ++j)
       for (size_t k = 0; k < lat4.size(2); ++k)
	 for (size_t l = 0; l < lat4.size(3); ++l)
	   lat4({i, j, k, l}) = n++;

  cout << endl;

  cout << "Neighborhoods with periodic boundary condition\n"
       << "==============================================\n";

  for (size_t i = 0; i < lat4.size(0); ++i)
    for (size_t j = 0; j < lat4.size(1); ++j)
      for (size_t k = 0; k < lat4.size(2); ++k)
	for (size_t l = 0; l < lat4.size(3); ++l)
	  {
	  vector<int *> vnn = VonNeumannNeighborhood<int>::get_instance().
	    get_neighbors(lat4, Periodic<int>::get_ptr_instance(), {i,j,k,l});
	  vector<int *> mn = MooreNeighborhood<int>::get_instance().
	    get_neighbors(lat4, Periodic<int>::get_ptr_instance(), {i,j,k,l});
	    assert(mn.size() == 80);
	    
	    cout << "Cell: " << lat4({i, j, k, l}) << "; VN neighbors: { ";
	    
	    for (auto p : vnn)
	      cout << *p << ' ';
	    
	    cout << "}; Moore neighbors { ";
	    
	    for (auto p : mn)
	    cout << *p << ' ';
	    
	    cout << "} " << endl;
	  } 

  cout << endl;

  cout << "Neighborhoods with reflect boundary condition\n"
       << "=============================================\n";

  for (size_t i = 0; i < lat4.size(0); ++i)
    for (size_t j = 0; j < lat4.size(1); ++j)
      for (size_t k = 0; k < lat4.size(2); ++k)
	for (size_t l = 0; l < lat4.size(3); ++l)
	  {
	  vector<int *> vnn = VonNeumannNeighborhood<int>::get_instance().
	    get_neighbors(lat4, Reflect<int>::get_ptr_instance(), {i,j,k,l});
	  vector<int *> mn = MooreNeighborhood<int>::get_instance().
	    get_neighbors(lat4, Reflect<int>::get_ptr_instance(), {i,j,k,l});
	    assert(mn.size() == 80);
	    
	    cout << "Cell: " << lat4({i, j, k, l}) << "; VN neighbors: { ";
	    
	    for (auto p : vnn)
	      cout << *p << ' ';
	    
	    cout << "}; Moore neighbors { ";
	    
	    for (auto p : mn)
	    cout << *p << ' ';
	    
	    cout << "} " << endl;
	  } 
  
  return 0;
}
