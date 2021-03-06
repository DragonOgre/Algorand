#include "SignatureBasedOnRSA.h"

BigInteger SignatureBasedOnRSA::Sign( const std::string& HashValue )
{
	BigInteger ming( HashValue ),code;
	code = rsa.PrivateEncrypt( ming );
//	code.TestOut();
//	cout << code.IntoBinaryS() <<endl<<""<<endl;
	return code;
}


void Signature::GetKey( std::ifstream& fin, BigInteger & N, BigInteger& E, BigInteger& D )
{
  rsa.Initialize(fin);
	N = rsa.N;  E = rsa.E; D = rsa.D;
}


bool Signature::Vertify(  const std::string& HashValue, const BigInteger& CODE, const BigInteger& N, const BigInteger&E  )
{
	BigInteger Hash( HashValue ),val;
	val = ModPow( CODE, E, N );
	if( val == Hash ) return true;
	return false;
}

/*
void SignatureBasedOnRSA::ComputeKey( int p, int q, BigInteger& N, BigInteger& E, BigInteger& D )
{
	BigInteger P(p),Q(q),ONE(1),eul;
	N = P*Q;  eul = (P-ONE)*(Q-ONE);
	BigInteger PDD( 65537 );
	E = PDD;
	D = ModInverse( E, eul );
}
*/

BigInteger Signature::EncryptWith( const std::string& HashValue, const BigInteger& N, const BigInteger& D )
{
	BigInteger ming(HashValue),val;
	val = ModPow( ming, D, N );
	return val;
}

BigInteger Signature::DecryptWith( const BigInteger& c, const BigInteger& N, const BigInteger& E )
{
	BigInteger val;
	val = ModPow( c, E, N );
	return val;
}

RSA Signature::rsa;
