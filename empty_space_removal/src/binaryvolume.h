#ifndef binaryvolume_h__
#define binaryvolume_h__

#include <vector>
#include <functional>
#include <assert.h>

template<typename ValType, typename In>
class BinVolBase 
{
public:
    BinVolBase() { }
    virtual ~BinVolBase() { }

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Create a 1's and 0's array from \p in_data. 
    /// \param isEmpty Functor that takes a \c ValType and decides if that voxel is empty.
    /// \param[in] in_data source data
    /// \param[out] out_binary Populated with a 1 for non-empty voxels, else 0.
    /// \note \p out_binary will be resized to the length of \p in_data.
    ///////////////////////////////////////////////////////////////////////////////
    virtual void 
    createBinaryVolume(In in, In end, std::function<bool(ValType)> empty);

    std::vector<bool> volume;
};

template<typename ValType, typename In>
void BinVolBase<ValType, In>::createBinaryVolume
(
    In in, 
    In end, 
    std::function<bool(ValType)> empty
)
{
    volume.resize(end-in);
    assert(end-in > 0 && "end-in > 0");
    std::vector<bool>::iterator out = volume.begin();

    while (in != end) {
        *out++ = empty(*in) ? 0 : 1;
        ++in;
    }
}

//template<typename ValType>
//class BinVol : public BinVolBase<ValType, typename std::vector<ValType>::const_iterator>
//{ };

template<typename ValType>
class BinVol : public BinVolBase < ValType, ValType* > 
{ };


template<typename ValType>
class SummedVolumeTableBase : public BinVol<ValType>
{
public:
    SummedVolumeTableBase() : BinVolBase() { }
    virtual ~SummedVolumeTableBase() { }

    virtual void create(ValType *data);

    BinVol<ValType> volume;

};

template<typename ValType>
void SummedVolumeTableBase<ValType>::create(ValType *data)
{
        
}

#endif // !binaryvolume_h__

