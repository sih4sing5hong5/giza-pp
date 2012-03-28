#include "transpair_model_hmm.h"
#include "forward_backward.h"

TransPairModelHMM::TransPairModelHMM(const Vector<WordIndex>& es,
                                     const Vector<WordIndex>& fs,
                                     const TModel<COUNT, PROB>& tTable,
                                     const AModel<PROB>&aTable,
                                     const AModel<PROB>&,const nmodel<PROB>&,
                                     double, double, const HMM* h)
    : transpair_model2(es,fs,tTable,aTable),
      network_(h->makeHMMNetwork(es,fs,0)) { }

TransPairModelHMM::~TransPairModelHMM() { delete network_; }

LogProb TransPairModelHMM::scoreOfMove(const Alignment&a,
                                       WordIndex _new_i,
                                       WordIndex j,
                                       double f) const {
  int new_i=_new_i;
  LogProb change=1.0;
  int old_i=a(j);
  if (old_i == new_i)
    change=1.0;
  else
  {
    int theJ=j-1;
    old_i--;
    new_i--;
    int jj=j-1;
    while(jj>0&&a(jj)==0)
      jj--;
    int theIPrev= (jj>0)?(a(jj)-1):0;
    if( j>1&&a(j-1)==0 )
      theIPrev+=l;
    if( old_i==-1 ){old_i = theIPrev;if(old_i<int(l))old_i+=l;}
    if( new_i==-1 ){new_i = theIPrev;if(new_i<int(l))new_i+=l;}
    int theIPrevOld=theIPrev,theIPrevNew=theIPrev;
    if( theJ==0 )
    {
      change*=network_->getAlphainit(new_i)/network_->getAlphainit(old_i);
    }
    do
    {
      if( new_i!=old_i )
      {
        change*=network_->nodeProb(new_i,theJ)/network_->nodeProb(old_i,theJ);
      }
      if( theJ>0)
        change*=network_->outProb(theJ,theIPrevNew,new_i)/network_->outProb(theJ,theIPrevOld,old_i);
      theIPrevOld=old_i;
      theIPrevNew=new_i;
      theJ++;
      if( theJ<int(m) && a(theJ+1)==0 )
      {
        if( new_i<int(l)) new_i+=l;
        if( old_i<int(l)) old_i+=l;
      }
    } while( theJ<int(m) && a(theJ+1)==0 );
    if(theJ==int(m))
    {
      change*=network_->getBetainit(new_i)/network_->getBetainit(old_i);
    }
    else
    {
      new_i=a(theJ+1)-1;
      if( new_i==-1)
        new_i=theIPrevNew;
      change*=network_->outProb(theJ,theIPrevNew,new_i)/network_->outProb(theJ,theIPrevOld,new_i);
    }
  }
  return change;
}

LogProb TransPairModelHMM::prob_of_target_and_alignment_given_source(const Alignment&al,
                                                                     bool verbose) const {
  double prob=1.0;
  int theIPrev=0;
  for(unsigned int j=1;j<=m;j++) {
    int theJ=j-1;
    int theI=al(j)-1;
    if (theI == -1)
      theI=(theIPrev%l)+l;
    prob *= network_->nodeProb(theI,theJ);
    if (verbose)
      cout << "NP " << network_->nodeProb(theI,theJ) << ' ';
    if (j==1) {
      prob *= network_->getAlphainit(theI);
      if (verbose)
        cout << "AP0 " << network_->getAlphainit(theI) << ' ';
    } else {
      prob *= network_->outProb(theJ,theIPrev,theI);
      if (verbose)
        cout << "AP1 " << network_->outProb(theJ,theIPrev,theI) << ' ';
    }
    theIPrev=theI;
    if (j == m) {
      prob*=network_->getBetainit(theI);
      if (verbose)
        cout << "AP2 " << network_->getBetainit(theI) << ' ';
    }
    if (verbose)
      cout << "j:"<<theJ<<" i:"<<theI << ";  ";
  }
  if( verbose )
    cout << '\n';
  return prob*network_->finalMultiply;
}

void TransPairModelHMM::computeScores(const Alignment& al, vector<double>& d) const {
  double prob1 = 1.0, prob2 = 1.0;
  int theIPrev=0;
  for(unsigned int j=1;j<=m;j++) {
    int theJ=j-1;
    int theI=al(j)-1;
    if( theI==-1 )
      theI=(theIPrev%l)+l;
    prob1*=network_->nodeProb(theI,theJ);
    if( j==1 ) {
      prob2*=network_->getAlphainit(theI);
    } else {
      prob2*=network_->outProb(theJ,theIPrev,theI);
    }
    theIPrev=theI;
    if( j==m ) {
      prob2*=network_->getBetainit(theI);
    }
  }
  d.push_back(prob1);
  d.push_back(prob2);
}
