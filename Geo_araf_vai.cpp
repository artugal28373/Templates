#include<iostream>
#include<vector>
#include<cstring>
#include<map>
#include<bitset>
#include<assert.h>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<set>
#include<queue>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<chrono>
#include<stack>
#include<deque>
#include<random>
//#define long long long
#define double long double
using namespace std;
const int N=1e6;

#define setp(a) cout<<setprecision(a)<<fixed
const double eps=1e-9,pi=acos(-1.0);

int sgn(double d)
{
  if(fabs(d)<eps)return 0;return d<0.0?-1:1;
}
struct point
{
  double x,y;
  point(){};point(double _x,double _y):x(_x),y(_y){}
  point operator+(point p){return point(x+p.x,y+p.y);}
  point operator-(point p){return point(x-p.x,y-p.y);}
  point operator*(double d){return point(x*d,y*d);}
  point operator/(double d){return point(x/d,y/d);}
  bool operator==(point p){return x==p.x&&y==p.y;}
  bool operator<(const point &p)const{return x<p.x||(x==p.x&&y<p.y);}
  double value(){return sqrt(x*x+y*y);}
  double dist(point p){return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));}
  point unitVector()
  {
    //invalid if vector is (0,0)
    double v=value();return point(x/v,y/v);
  }
  double operator*(point p)
  {
    return x*p.x+y*p.y;//0 if vectors are perpendicular;
  }
  double operator^(point p)
  {
    return x*p.y-y*p.x;//0 if two vectors are same
    //signed area of the parallelogram by two vector
    //positive if p is ccw to the vector
  }
  point rotateCCW(double a)//radian
  {
    return point(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));
  }
  point rotateCCW90(){return point(-y,x);}
  point rotateCCW180(){return point(-x,-y);}
  point rotateCCW270(){return point(y,-x);}
};
double radToDeg(double r){return r*180.0/pi;}
double degToRed(double d){return d*pi/180.0;}
double modifiedatan2(point p)//counter-clockwise full angle with positive x axis
{
  double ang=atan2(p.y,p.x);if(ang<0)ang+=pi+pi;//carefull
  return radToDeg(ang);//deg return
}
struct line
{
  point p,v;//v is vector,going through p;
  line(){}
  line(point _p,point _v):p(_p),v(_v){}
  void makeLine(point p1,point p2){p=p1,v=p2-p1;}
  bool onLine(point p1)
  {
    if(sgn(v^(p1-p))!=0)return false;//area of triangle has to be 0
    return true;
  }
  double pointDist(point p1)
  {
    //area of triangle/base of triangle
    return abs((v^(p1-p))/v.value());//signed based on cw ans ccw
  }
  line perpendicular(point p1){return line(p1,v.rotateCCW90());}
  point intersection(line l)
  {
    //no solution for parallel line.
    return p+v*((l.v^(p-l.p))/(v^l.v));
  }
};
struct segment
{
  point a,b;
  segment(){}
  segment(point _a,point _b):a(_a),b(_b){}
  //onLine and onSegment
  bool onLine(point p)
  {
    line l;l.makeLine(a,b);
    if(!l.onLine(p))return false;
    if(p.x>=min(a.x,b.x)&&p.x<=max(a.x,b.x)&&p.y>=min(a.y,b.y)&&p.y<=max(a.y,b.y))
      return true;//precision
    return false;
  }
  int segmentIntersect(segment sg)
  {
    int s1,s2,s3,s4;
    int d1=sgn(s1=(b-a)^(sg.a-a)),d2=sgn(s2=(b-a)^(sg.b-a));
    int d3=sgn(s3=(sg.b-sg.a)^(a-sg.a)),d4=sgn(s4=(sg.b-sg.a)^(b-sg.a));
    if((d1^d2)==-2&&(d3^d4)==-2)return 1;
    else if(d1==0&&sgn((a-sg.a)*(b-sg.a))<=0)return 2;
    else if(d2==0&&sgn((a-sg.b)*(b-sg.b))<=0)return 2;
    else if(d3==0&&sgn((sg.a-a)*(sg.b-a))<=0)return 2;
    else if(d4==0&&sgn((sg.a-b)*(sg.b-b))<=0)return 2;
    return 0;
  }
  //this is a very bad way to do this
  double segmentToPointDist(point p)
  {
    line l,r;l.makeLine(a,b);r=l.perpendicular(p);
    double ret=min(a.dist(p),b.dist(p));
    if(onLine(l.intersection(r)))ret=l.pointDist(p);
    return ret;
  }
  double segmentSegmentDist(segment sg)
  {
    if(segmentIntersect(sg))return 0;
    double ret=segmentToPointDist(sg.a);
    ret=min(ret,segmentToPointDist(sg.b));
    ret=min(ret,sg.segmentToPointDist(a));
    ret=min(ret,sg.segmentToPointDist(b));
    return ret;
  }
};
struct circle
{
  double x,y,r;
  circle(){};circle(double _x,double _y,double _r):x(_x),y(_y),r(_r){}
};
struct triangle
{
  point a,b,c;
  triangle(){}
  triangle(point _a,point _b,point _c):a(_a),b(_b),c(_c){}
  bool inTriangle(point p)
  {
    int s1=abs((b-a)^(c-a));
    int s2=abs((a-p)^(b-p))+abs((b-p)^(c-p))+abs((c-p)^(a-p));
    return sgn(s1-s2)==0;
  }
  point inCenter()//intersection of the angle bisector, center of inCircle
  {
    double bc=b.dist(c),ca=c.dist(a),ab=a.dist(b);
    double p=ab+bc+ca;//cout<<p<<endl;
    return point((bc*a.x+ca*b.x+ab*c.x)/p,(bc*a.y+ca*b.y+ab*c.y)/p);
  }
  //center of circles going through three points
  point circumCenter()//intersection of perpendicular bisector of the side,
  {
    double x=(a.x*a.x+a.y*a.y)*(b.y-c.y)+(b.x*b.x+b.y*b.y)*(c.y-a.y)+(c.x*c.x+c.y*c.y)*(a.y-b.y);
    double d=2*(a.x*(b.y-c.y)-a.y*(b.x-c.x)+b.x*c.y-c.x*b.y);
    double y=(a.x*a.x+a.y*a.y)*(c.x-b.x)+(b.x*b.x+b.y*b.y)*(a.x-c.x)+(c.x*c.x+c.y*c.y)*(b.x-a.x);
    return point(x/d,y/d);
  }
  point centroid()//intersection of mid points of each side
  {
    return point((a.x+b.x+c.x)/3.0,(a.y+b.y+c.y)/3.0);
  }
};
struct polygon
{
  vector<point>p,h;
  polygon(){};
  polygon(vector<point>_p):p(_p){}
  /*
  in a N*N grid a convexHull can have maximum N^(2/3) vertices of lattice point
  after omitting straight line point. for random input it is N^(1/3);
  returns counter-clock-wise, a path, not closed circuit
  */
  void convexHull()
  {
    sort(p.begin(),p.end());int n=p.size(),top=0;//polygon are changed
    vector<point>stck(n+10);
    for(int i=n-1;i>=0;i--)
    {
      stck[++top]=p[i];//>=0 to omit straight line point;
      while(top>2)
      {
        if(((stck[top-1]-stck[top-2])^(stck[top]-stck[top-2]))>=0)
          stck[top-1]=stck[top],top--;
        else break;
      }
    }
    while(top>0)h.push_back(stck[top--]);
    for(int i=0;i<n;i++)
    {
      stck[++top]=p[i];//>=0 to omit straight line point;
      while(top>2)
      {
        if(((stck[top-1]-stck[top-2])^(stck[top]-stck[top-2]))>=0)
          stck[top-1]=stck[top],top--;
        else break;
      }
    }
    top--;
    while(top>0)h.push_back(stck[top--]);
    if(h.size()>1)h.pop_back();
  }
  double hullArea()//can be used for polygon area too
  {
    convexHull();double ret=0;
    int n=h.size();
    for(int i=1;i<n;i++)ret+=(h[i]-h[0])^(h[(i+1)%n]-h[0]);
    return abs(ret/2.0);//signed, positive for cw
  }
  double rotateCalipers()//for diameter
  {
    int n=h.size();
    double ans=0;int j=1;
    for(int i=0;i<n;i++)
    {
      while(abs((h[i+1]-h[j+1])^(h[i]-h[j+1]))>abs((h[i+1]-h[j])^(h[i]-h[j])))
        j=(j+1)%n;
      ans=max(ans,h[j].dist(h[i]));
      ans=max(ans,h[j].dist(h[(i+1)%n]));
    }
    return ans;
  }
  void minmumBoundingBox()//for minimum rectangle area and perimeter
  {
    int n=h.size(),l=1,r=1,u=1;
    double area=1e18,per=1e18;
    for(int i=0;i<n;i++)
    {
      point p=(h[(i+1)%n]-h[i])/h[(i+1)%n].dist(h[i]);
      while(p*(h[r%n]-h[i])<p*(h[(r+1)%n]-h[i]))r++;
      while(u<r||(p^(h[u%n]-h[i]))<(p^(h[(u+1)%n]-h[i])))u++;
      while(l<u||(p*(h[l%n]-h[i]))>(p*(h[(l+1)%n]-h[i])))l++;
      double a=p*(h[r%n]-h[i])-p*(h[l%n]-h[i]);
      double b=fabs((h[i]-h[u%n])^((h[(i+1)%n]-h[u%n])/h[i].dist(h[(i+1)%n])));

      area=min(area,a*b);per=min(per,a+a+b+b);
    }
  }
  //return 1 for inside, 0 for on and -1 for outside
  //point is ccw oriented with no three collinear point
  //obviously use integer
  int inConvex(point p)
  {
    int n=h.size();assert(n>=3);////////////
    int lo=1,hi=n-1;
    while(hi-lo>1)
    {
      int md=(lo+hi)/2;
      if(((h[md]-h[0])^(p-h[0]))>0)lo=md;//carefull
      else hi=md;
    }
    bool in=triangle(h[0],h[lo],h[hi]).inTriangle(p);
    if(!in)return -1;

    if(sgn((h[lo]-h[lo-1])^(p-h[lo-1]))==0)return 0;
    if(sgn((h[hi]-h[lo])^(p-h[lo]))==0)return 0;
    if(sgn((h[hi]-h[(hi+1)%n])^(p-h[(hi+1)%n]))==0)return 0;
    return 1;
  }
};
int main()
{
  setp(10);ios_base::sync_with_stdio(0);cin.tie(0);

  int n;cin>>n;vector<pair<point,int> >p(n);
  for(int i=0;i<n;i++)cin>>p[i].first.x>>p[i].first.y,p[i].second=i+1;

  sort(p.begin(),p.end(),[&](pair<point,int>a,pair<point,int>b){
    return modifiedatan2(a.first)<modifiedatan2(b.first);
  });
  double mn=1e9;int a,b;
  for(int i=0;i<n;i++)
  {
    int j=(i+1)%n;
    double df=modifiedatan2(p[i].first)-modifiedatan2(p[j].first);
    if(df<0)df+=360;if(df>180)df=360-df;

    if(df<mn)mn=df,a=p[i].second,b=p[j].second;
  }
  cout<<a<<" "<<b<<endl;
  return 0;
}
