﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "RefAdditionUint8Workload.hpp"

#include "Addition.hpp"
#include "RefWorkloadUtils.hpp"

#include "Profiling.hpp"

#include <vector>

namespace armnn
{

void RefAdditionUint8Workload::Execute() const
{
    ARMNN_SCOPED_PROFILING_EVENT(Compute::CpuRef, "RefAdditionUint8Workload_Execute");

    const TensorInfo& inputInfo0 = GetTensorInfo(m_Data.m_Inputs[0]);
    const TensorInfo& inputInfo1 = GetTensorInfo(m_Data.m_Inputs[1]);
    const TensorInfo& outputInfo = GetTensorInfo(m_Data.m_Outputs[0]);

    auto dequant0 = Dequantize(GetInputTensorDataU8(0, m_Data), inputInfo0);
    auto dequant1 = Dequantize(GetInputTensorDataU8(1, m_Data), inputInfo1);

    std::vector<float> results(outputInfo.GetNumElements());

    Addition(inputInfo0.GetShape(),
             inputInfo1.GetShape(),
             outputInfo.GetShape(),
             dequant0.data(),
             dequant1.data(),
             results.data());

    Quantize(GetOutputTensorDataU8(0, m_Data), results.data(), outputInfo);
}

} //namespace armnn
