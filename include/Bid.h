#ifndef BID_H
#define BID_H


class Bid
{
    public:
        Bid();
        virtual ~Bid();
        void setTraget(int);
        int  getTraget();
        void setBiddingMoney(double);
        double getBiddingMoney();
    protected:
    private:
        int target;
        double biddingMoney;
};

#endif // BID_H
