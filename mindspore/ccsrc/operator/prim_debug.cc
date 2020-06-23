/**
 * Copyright 2019 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "pipeline/static_analysis/param_validator.h"
#include "pipeline/static_analysis/prim.h"
#include "operator/ops.h"
#include "pipeline/static_analysis/utils.h"
#include "utils/symbolic.h"

namespace mindspore {
namespace abstract {
AbstractBasePtr InferImplDebug(const AnalysisEnginePtr &, const PrimitivePtr &primitive,
                               const AbstractBasePtrList &args_spec_list) {
  // Inputs: a tensor(value)
  const std::string op_name = primitive->name();

  CheckArgsSize(op_name, args_spec_list, 1);
  auto tensor_value = CheckArg<AbstractTensor>(op_name, args_spec_list, 0);

  int tensor_rank = SizeToInt(tensor_value->shape()->shape().size());
  if (tensor_rank == 0) {
    MS_LOG(EXCEPTION) << op_name << " summary evaluator second arg should be an tensor, but got a scalar, rank is 0";
  }

  return std::make_shared<AbstractTuple>(AbstractBasePtrList({tensor_value->Broaden()}));
}
}  // namespace abstract
}  // namespace mindspore
