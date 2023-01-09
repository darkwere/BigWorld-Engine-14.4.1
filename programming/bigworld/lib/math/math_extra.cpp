#include "pch.hpp"
#include <limits>
#include "math/math_extra.hpp"
#include "cstdmf/bwrandom.hpp"
#include "cstdmf/debug.hpp"
#include "cstdmf/guard.hpp"

namespace BW
{

/**
 *	This applies Gram-Schmidt orgthonalisation to the vectors v1, v2 and v3 and
 *	returns the result in e1, e2 and e3.  The vectors v1, v2, v3 should be
 *	linearly indepedant, non-zero vectors.
 *
 *  See http://en.wikipedia.org/wiki/Gram-Schmidt_process for details of 
 *	Gram-Schmidt orthogonalisation.
 *
 *  @param v1, v2, v3	The vectors to orthonormalise.
 *  @param e1, e2, e3	The orthonormalised vectors.
 */
void orthogonalise(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3,
				 Vector3 &e1, Vector3 &e2, Vector3 &e3)
{
	BW_GUARD;

	Vector3 u1 = v1; 

	Vector3 p1; 
	p1.projectOnto(v2, u1);
	Vector3 u2 = v2 - p1;
	
	Vector3 p2; 
	p2.projectOnto(v3, u1);
	Vector3 p3; 
	p3.projectOnto(v3, u2);
	Vector3 u3 = v3 - p2 - p3;
	
	u1.normalise();
	u2.normalise();
	u3.normalise();

	e1 = u1; e2 = u2; e3 = u3;
}

///This is the max power of two on 32 bit machines
static unsigned long MAX_POW_2 = 2147483648UL;

uint32 largerPow2( uint32 number )
{
    BW_GUARD;

	if(number == 0)
	{
		return 1;
	}
	//Do the best we can - return a smaller pow 2 element
	else if (number > MAX_POW_2)
	{
		WARNING_MSG( "BW::largerPow2 returning a smaller power of 2 "
			"as %u is too large\n", number );
		return MAX_POW_2;
	}

	--number;
	number |= number >> 1;
	number |= number >> 2;
	number |= number >> 4;
	number |= number >> 8;
	number |= number >> 16;
	return ++number;
}


uint32 smallerPow2( uint32 number )
{
	BW_GUARD;

	return largerPow2( number ) / 2;
}

bool isPow2( uint32 value )
{
	return ( ( value & ( value - 1 ) ) == 0 );
}

// Sourced from: http://aggregate.org/MAGIC/#Log2%20of%20an%20Integer
uint32 ones32( uint32 x )
{
    /* 32-bit recursive reduction using SWAR...
	   but first step is mapping 2-bit values
	   into sum of 2 1-bit values in sneaky way
	*/
        x -= ((x >> 1) & 0x55555555);
        x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
        x = (((x >> 4) + x) & 0x0f0f0f0f);
        x += (x >> 8);
        x += (x >> 16);
        return(x & 0x0000003f);
}

// Log2 of an integer.
// Sourced from: http://aggregate.org/MAGIC/#Log2%20of%20an%20Integer
uint32 log2ceil( uint32 x )
{
	register int y = (x & (x - 1));

	y |= -y;
	y >>= (32 - 1);
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
#ifdef	LOG0UNDEFINED
	return(ones32(x) - 1 - y);
#else
	return(ones32(x >> 1) - y);
#endif
}

uint32 roundUpToPow2Multiple( uint32 value, uint32 multiple )
{
	assert( isPow2( multiple ) == true );
	return ( value + ( multiple - 1 ) ) & ~( ( multiple - 1 ) );
}

/**
 *	@pre @a minComponentValue is not more than @a maxComponentValue.
 *	@post Returned a vector with random elements in the range
 *		[@a minComponentValue, @a maxComponentValue] generated
 *		by @a randomSource.
 */
Vector3 createRandomVector3( BW_NAMESPACE BWRandom & randomSource,
	float minComponentValue, float maxComponentValue )
{
	BW_GUARD;

	MF_ASSERT( minComponentValue <= maxComponentValue );

	Vector3 result;

	for (int i = 0; i < 3; ++i)
	{
		result[i] = randomSource( minComponentValue, maxComponentValue );
	}

	return result;
}


/**
 *	@pre @a minComponentAbsoluteValue is not more
 *		than @a maxComponentAbsoluteValue.
 *	@pre @a minComponentAbsoluteValue is more than zero.
 *	@post Returned a vector with random elements with absolute values in the
 *		range [@a minComponentAbsoluteValue, @a maxComponentAbsoluteValue]
 *		generated by @a randomSource. The sign (+/-) of each value is random.
 */
Vector3 createRandomNonZeroVector3( BW_NAMESPACE BWRandom & randomSource,
	float minComponentAbsoluteValue, float maxComponentAbsoluteValue )
{
	BW_GUARD;
	
	MF_ASSERT( 0.0f < minComponentAbsoluteValue );
	MF_ASSERT( minComponentAbsoluteValue <= maxComponentAbsoluteValue );

	Vector3 result;

	for (int i = 0; i < 3; ++i)
	{
		result[i] = randomSource(
			minComponentAbsoluteValue, maxComponentAbsoluteValue );
		if (randomSource( 0, 1 ))
		{
			result[i] *= -1.0f;
		}
	}

	return result;
}


/**
 *	@pre @a minComponentValue is not more than @a maxComponentValue.
 *	@post A matrix with random elements in the range
 *		[@a minComponentValue, @a maxComponentValue] generated
 *		by @a randomSource.
 */
Matrix createRandomTransform( BW_NAMESPACE BWRandom & randomSource,
	float minComponentValue, float maxComponentValue )
{
	BW_GUARD;

	MF_ASSERT( minComponentValue <= maxComponentValue );

	Matrix result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result(i, j) = randomSource( minComponentValue, maxComponentValue );
		}
	}

	return result;
}


/**
 *	@return A matrix applying a random rotation. Randomness
 *		generated by @a randomSource.
 */
Matrix createRandomRotate( BW_NAMESPACE BWRandom & randomSource )
{
	BW_GUARD;

	const float PI = BW::MATH_PI;

	Matrix result;
	result.setRotateX( randomSource( -PI, PI ) );
	result.postRotateY( randomSource( -PI, PI ) );
	result.postRotateZ( randomSource( -PI, PI ) );

	return result;
}


/**
 *	@pre @a translationRange is positive.
 *	@post A matrix applying a random transform with only rotation and
 *		translation components. Randomness generated by @a randomSource.
 */
Matrix createRandomRotateTranslate( BW_NAMESPACE BWRandom & randomSource,
	float translationRange )
{
	BW_GUARD;

	MF_ASSERT( 0.0f <= translationRange );

	Matrix result = createRandomRotate( randomSource );
	result.postTranslateBy( createRandomVector3(
		randomSource, -translationRange, translationRange ) );

	return result;
}


/**
 *	@pre @a translationRange is positive.
 *	@pre @a maxScale is at least numeric_limit<float>::epsilon().
 *	@post A matrix applying a random transform with only rotation,
 *		translation, and scale components. The scale is non-zero. Randomness
 *		generated by @a randomSource.
 */
Matrix createRandomRotateTranslateScale( BW_NAMESPACE BWRandom & randomSource,
	float translationRange, float maxScale )
{
	BW_GUARD;

	MF_ASSERT( 0.0f <= translationRange );
	MF_ASSERT( std::numeric_limits<float>::epsilon() <= maxScale );

	Matrix result;
	result.setScale( createRandomNonZeroVector3( randomSource,
		std::numeric_limits<float>::epsilon(), maxScale ) );
	result.postMultiply(
		createRandomRotateTranslate( randomSource, translationRange ) );
	return result;
}

} // namespace BW

// math_extra.cpp
