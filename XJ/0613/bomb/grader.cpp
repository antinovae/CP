//Code By CXY07 - It's My Fiesta.
#include"bomb.h"
#include<vector>
#include<fstream>
#include<iostream>

int _op, _n, _m, _k;
bool _vis[(int)(1e6 + 10)];
std::vector<int> _v, _v2;
std::ifstream _fin;
std::ofstream _fout;

void _WA(int _x) { _fout << _x << std::endl; exit(0); }

int cut_wire(int x) {
	if(_op != 2) _WA(8);
	if(x < 0 || x >= _n) _WA(5);
	if(_v[x]) _WA(6);
	if(_vis[x]) _WA(9);
	_vis[x] = true;
	return _v2[x];
}

signed main () {
	_fin.open("1.txt");
	_fin >> _op;
	_fin.close();
	_fin.open("2.txt");
	_fin >> _n >> _m >> _k; 
	_v.resize(_n);
	for(int i = 0; i < _n; ++i) _fin >> _v[i];
	if(_op == 1) {
		_fout.open("3.txt");
		for(int i=0;i<_n;i++){
		    std::cerr<<_v[i]<<" ";
		}
		std::cerr<<std::endl;
		auto _res = run_X(_n, _m, _v);
		if((int)_res.first.size() != _n) _WA(1);
		if(_res.second >= (1ll << 41) || _res.second < 0) _WA(2);
		for(int i = 0; i < _n; ++i)
			if(_res.first[i] < -1 || _res.first[i] > 1) _WA(3);
		int _num = 0;
		for(int i = 0; i < _n; ++i) if(~_res.first[i]) ++_num;
		if(_num > _m) _WA(4);
		_fout << 0 << std::endl << _res.second << std::endl;
		for(int i = 0; i < _n; ++i) _fout << _res.first[i] << ' ';
		_fout << std::endl;
	} else {
		_fin.close();
		_fin.open("3.txt");
		_fout.open("4.txt");
		int _state; long long _INFO;
		_fin >> _state;
		if(_state) _WA(_state);
		_fin >> _INFO; _v2.resize(_n);
		for(int i = 0; i < _n; ++i) _fin >> _v2[i];
		for(int i=0;i<_n;i++){
		    std::cerr<<_v2[i]<<" ";
		}
		std::cerr<<_INFO<<std::endl;
		run_C(_n, _INFO);
		for(int i = 0; i < _n; ++i) if(_vis[i] == _v[i]) _WA(7);
		_fout << 0 << std::endl;
	}
	return 0;
}
