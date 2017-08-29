/*
  This file is part of LibCA.
  Copyright (C) 2015 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to 

  Alejandro Mujica

  aledrums@gmail.com
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
