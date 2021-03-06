﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// See LICENSE file in the project root for full license information.
//
#include "NeonWorkloadUtils.hpp"
#include "backends/ArmComputeTensorUtils.hpp"
#include "backends/ArmComputeUtils.hpp"
#include "backends/CpuTensorHandle.hpp"
#include "backends/NeonTensorHandle.hpp"

#include "armnn/Utils.hpp"
#include "armnn/Exceptions.hpp"

#include <cstring>
#include <boost/assert.hpp>
#include <boost/cast.hpp>
#include <boost/format.hpp>

#include "Profiling.hpp"

#include "NeonLayerSupport.hpp"
#include "../../../include/armnn/Types.hpp"
#include "Half.hpp"

using namespace armnn::armcomputetensorutils;

namespace armnn
{

// Allocates a tensor and copy the contents in data to the tensor contents.
template<typename T>
void InitialiseArmComputeTensorData(arm_compute::Tensor& tensor, const T* data)
{
    InitialiseArmComputeTensorEmpty(tensor);
    CopyArmComputeITensorData(data, tensor);
}

template void InitialiseArmComputeTensorData(arm_compute::Tensor& tensor, const Half* data);
template void InitialiseArmComputeTensorData(arm_compute::Tensor& tensor, const float* data);
template void InitialiseArmComputeTensorData(arm_compute::Tensor& tensor, const uint8_t* data);
template void InitialiseArmComputeTensorData(arm_compute::Tensor& tensor, const int32_t* data);

void InitializeArmComputeTensorDataForFloatTypes(arm_compute::Tensor& tensor,
                                                 const ConstCpuTensorHandle* handle)
{
    BOOST_ASSERT(handle);
    switch(handle->GetTensorInfo().GetDataType())
    {
        case DataType::Float16:
            InitialiseArmComputeTensorData(tensor, handle->GetConstTensor<Half>());
            break;
        case DataType::Float32:
            InitialiseArmComputeTensorData(tensor, handle->GetConstTensor<float>());
            break;
        default:
            BOOST_ASSERT_MSG(false, "Unexpected floating point type.");
    }
};

} //namespace armnn
