// Grid walk
#include<iostream>
#include <stdio.h>
#include <sstream>
#include<fstream>
#include <limits.h>
#include <vector>
#include<map>
#include<queue>
using namespace std;

struct coordinates {
	int x = 0;
	int y = 0;
	bool  operator==(const coordinates &o) const {
		return x == o.x && y == o.y;
	}

	bool  operator<(const coordinates &o) const {
		return x < o.x || (x == o.x && y < o.y);
	}
};
queue<coordinates> q;
int cntr = 0;
map<coordinates, bool> visited;
bool check(coordinates c) {
	int x = abs(c.x);
	int y = abs(c.y);
	vector<int> xc;
	vector<int>yc;
	while (x)
	{
		xc.push_back(x % 10);
		x /= 10;
	}
	while (y)
	{
		yc.push_back(y % 10);
		y /= 10;
	}
	int sum = 0;
	for (vector<int>::iterator it = xc.begin(); it != xc.end(); it++)
		sum += *it;
	for (vector<int>::iterator it = yc.begin(); it != yc.end(); it++)
		sum += *it;
	if (sum <= 19)
		return true;
	else
		return false;
}
void new_cord(coordinates old)
{
	coordinates newc;
	std::map<coordinates, bool>::iterator it;
	//go right
	newc.x = old.x + 1;
	newc.y = old.y;

	if (visited.find(newc) == visited.end() && check(newc)) {
		q.push(newc);
		visited[newc] = true;
	}
	//go left
	newc.x = old.x - 1;
	newc.y = old.y;
	if (visited.find(newc) == visited.end() && check(newc)) {
		q.push(newc);
		visited[newc] = true;
	}
	//go Up
	newc.x = old.x;
	newc.y = old.y + 1;
	if (visited.find(newc) == visited.end() && check(newc)) {
		q.push(newc);
		visited[newc] = true;
	}
	//go Down
	newc.x = old.x;
	newc.y = old.y - 1;
	if (visited.find(newc) == visited.end() && check(newc)) {
		q.push(newc);
		visited[newc] = true;
	}
}
void compute_cord()
{
	coordinates old;
	while (!q.empty())
	{
		old = q.front();
		q.pop();
		new_cord(old);
	}
}
int main()
{
	coordinates old;
	old.x = 0;
	old.y = 0;
	q.push(old);
	pair<coordinates, bool> p(old, true);
	visited.insert(p);
	compute_cord();
	cout << visited.size();

}
