# $ gyp src/iroha.gyp --depth=. -f make
# maybe with --generator-output=src
{
    'make_global_settings': [
    ],
    'target_defaults': {
        'cflags': ['-fPIC', '-Wall', '-Wno-sign-compare'],
        'defines': ['PACKAGE="iroha"', 'VERSION="0.0.1"'],
        'xcode_settings': {
            'OTHER_CFLAGS': [
            ],
        },
    },
    'targets': [
        {
            'target_name': 'iroha',
            'product_name': 'iroha',
            'type': 'executable',
            'include_dirs': [
                './',
            ],
            'sources': [
                'main.cpp',
            ],
            'dependencies': [
                ':libiroha'
            ],
        },
        {
            'target_name': 'numeric_test',
            'product_name': 'numeric_test',
            'type': 'executable',
            'include_dirs': [
                './',
            ],
            'sources': [
                'numeric/numeric_test.cpp',
            ],
            'dependencies': [
                ':numeric'
            ],
        },
        {
            'target_name': 'libiroha',
            'product_name': 'iroha',
            'type': 'static_library',
            'include_dirs': [
                './',
            ],
            'sources': [
                'builder/design_builder.cpp',
                'builder/design_builder.h',
                'builder/fsm_builder.cpp',
                'builder/fsm_builder.h',
                'builder/reader.cpp',
                'builder/reader.h',
                'builder/platform_builder.cpp',
                'builder/platform_builder.h',
                'builder/tree_builder.cpp',
                'builder/tree_builder.h',
                'design/design_tool.cpp',
                'design/design_tool.h',
                'design/design_util.cpp',
                'design/design_util.h',
                'design/validator.cpp',
                'design/validator.h',
                'iroha/common.h',
                'iroha/dot/dot.cpp',
                'iroha/dot/dot.h',
                'iroha/i_design.cpp',
                'iroha/i_design.h',
                'iroha/i_platform.cpp',
                'iroha/i_platform.h',
                'iroha/insn_operands.h',
                'iroha/iroha.cpp',
                'iroha/iroha.h',
                'iroha/iroha_main.cpp',
                'iroha/iroha_main.h',
                'iroha/logging.cpp',
                'iroha/logging.h',
                'iroha/numeric.h',
                'iroha/object_pool.h',
                'iroha/opt_api.h',
                'iroha/resource_attr.cpp',
                'iroha/resource_attr.h',
                'iroha/resource_class.cpp',
                'iroha/resource_class.h',
                'iroha/resource_params.cpp',
                'iroha/resource_params.h',
                'iroha/stl_util.h',
                'iroha/test_util.h',
                'iroha/writer_api.h',
                'opt/array_elimination.cpp',
                'opt/array_elimination.h',
                'opt/array_split_rdata.cpp',
                'opt/array_split_rdata.h',
                'opt/bb_collector.cpp',
                'opt/bb_collector.h',
                'opt/bb_set.cpp',
                'opt/bb_set.h',
                'opt/clean/empty_state.cpp',
                'opt/clean/empty_state.h',
                'opt/clean/empty_table.cpp',
                'opt/clean/empty_table.h',
                'opt/clean/pseudo_resource.cpp',
                'opt/clean/pseudo_resource.h',
                'opt/clean/unreachable_state.cpp',
                'opt/clean/unreachable_state.h',
                'opt/clean/unused_register.cpp',
                'opt/clean/unused_register.h',
                'opt/clean/unused_resource.cpp',
                'opt/clean/unused_resource.h',
                'opt/constant/constant_propagation.cpp',
                'opt/constant/constant_propagation.h',
                'opt/common.h',
                'opt/compound.cpp',
                'opt/compound.h',
                'opt/data_flow_collector.cpp',
                'opt/data_flow_collector.h',
                'opt/data_flow.cpp',
                'opt/data_flow.h',
                'opt/optimizer_log.cpp',
                'opt/optimizer_log.h',
                'opt/delay_info.cpp',
                'opt/delay_info.h',
                'opt/dominator_tree_builder.cpp',
                'opt/dominator_tree_builder.h',
                'opt/dominator_tree.cpp',
                'opt/dominator_tree.h',
                'opt/loop/loop_block.cpp',
                'opt/loop/loop_block.h',
                'opt/optimizer.cpp',
                'opt/optimizer.h',
                'opt/opt_util.cpp',
                'opt/opt_util.h',
                'opt/pass.cpp',
                'opt/pass.h',
                'opt/branch_elimination/branch_elimination_pass.cpp',
                'opt/branch_elimination/branch_elimination_pass.h',
                'opt/pipeline/insn_condition.cpp',
                'opt/pipeline/insn_condition.h',
                'opt/pipeline/pipeliner.cpp',
                'opt/pipeline/pipeliner.h',
                'opt/pipeline/pipeline_pass.cpp',
                'opt/pipeline/pipeline_pass.h',
                'opt/pipeline/reg_info.cpp',
                'opt/pipeline/reg_info.h',
                'opt/pipeline/scheduled_shape.cpp',
                'opt/pipeline/scheduled_shape.h',
                'opt/pipeline/stage_scheduler.cpp',
                'opt/pipeline/stage_scheduler.h',
                'opt/profile/profile.cpp',
                'opt/profile/profile.h',
                'opt/sched/bb_data_path.cpp',
                'opt/sched/bb_data_path.h',
                'opt/sched/bb_scheduler.cpp',
                'opt/sched/bb_scheduler.h',
                'opt/sched/bb_wire_plan.cpp',
                'opt/sched/bb_wire_plan.h',
                'opt/sched/common.h',
                'opt/sched/data_path_set.cpp',
                'opt/sched/data_path_set.h',
                'opt/sched/explorer.cpp',
                'opt/sched/explorer.h',
                'opt/sched/path_node.cpp',
                'opt/sched/path_node.h',
                'opt/sched/plan_evaluator.cpp',
                'opt/sched/plan_evaluator.h',
                'opt/sched/resource_conflict_tracker.cpp',
                'opt/sched/resource_conflict_tracker.h',
                'opt/sched/resource_entry.cpp',
                'opt/sched/resource_entry.h',
                'opt/sched/resource_replica_assigner.cpp',
                'opt/sched/resource_replica_assigner.h',
                'opt/sched/resource_tracker.cpp',
                'opt/sched/resource_tracker.h',
                'opt/sched/relocator.cpp',
                'opt/sched/relocator.h',
                'opt/sched/sched_block.cpp',
                'opt/sched/sched_block.h',
                'opt/sched/sched_pass.cpp',
                'opt/sched/sched_pass.h',
                'opt/sched/table_scheduler.cpp',
                'opt/sched/table_scheduler.h',
                'opt/sched/transition_fixup.cpp',
                'opt/sched/transition_fixup.h',
                'opt/sched/virtual_resource.cpp',
                'opt/sched/virtual_resource.h',
                'opt/sched/virtual_resource_set.cpp',
                'opt/sched/virtual_resource_set.h',
                'opt/sched/wire_plan.cpp',
                'opt/sched/wire_plan.h',
                'opt/ssa/condition_value_range.cpp',
                'opt/ssa/condition_value_range.h',
                'opt/ssa/phi_builder.cpp',
                'opt/ssa/phi_builder.h',
                'opt/ssa/phi_cleaner.cpp',
                'opt/ssa/phi_cleaner.h',
                'opt/ssa/phi_injector.cpp',
                'opt/ssa/phi_injector.h',
                'opt/ssa/ssa_converter.cpp',
                'opt/ssa/ssa_converter.h',
                'opt/ssa/ssa.cpp',
                'opt/ssa/ssa.h',
                'opt/study.cpp',
                'opt/study.h',
                'opt/unroll/state_copier.cpp',
                'opt/unroll/state_copier.h',
                'opt/unroll/unroll_pass.cpp',
                'opt/unroll/unroll_pass.h',
                'opt/unroll/unroller.cpp',
                'opt/unroll/unroller.h',
                'platform/platform.cpp',
                'platform/platform.h',
                'platform/platform_db.cpp',
                'platform/platform_db.h',
                'writer/connection.cpp',
                'writer/connection.h',
                'writer/dot_writer.cpp',
                'writer/dot_writer.h',
                'writer/exp_writer.cpp',
                'writer/exp_writer.h',
                'writer/html_writer.cpp',
                'writer/html_writer.h',
                'writer/module_template.cpp',
                'writer/module_template.h',
                'writer/names.cpp',
                'writer/names.h',
                'writer/writer.cpp',
                'writer/writer.h',
            ],
            'dependencies': [
                ':base',
                ':numeric',
                ':verilog_writer'
            ],
        },
        {
            'target_name': 'numeric',
            'product_name': 'numeric',
            'type': 'static_library',
            'include_dirs': [
                './',
            ],
            'sources': [
                'numeric/numeric_manager.cpp',
                'numeric/numeric_manager.h',
                'numeric/numeric_literal.cpp',
                'numeric/numeric_literal.h',
                'numeric/numeric.cpp',
                'numeric/numeric.h',
                'numeric/numeric_op.cpp',
                'numeric/numeric_op.h',
                'numeric/numeric_value.cpp',
                'numeric/numeric_value.h',
                'numeric/numeric_width.cpp',
                'numeric/numeric_width.h',
                'numeric/wide_op.cpp',
                'numeric/wide_op.h',
            ],
            'dependencies': [
                ':base',
            ],
        },
        {
            'target_name': 'verilog_writer',
            'product_name': 'verilog_writer',
            'type': 'static_library',
            'include_dirs': [
                './',
            ],
            'sources': [
                'writer/verilog/array.cpp',
                'writer/verilog/array.h',
                'writer/verilog/array_rdata.cpp',
                'writer/verilog/array_rdata.h',
                'writer/verilog/axi/axi_controller.cpp',
                'writer/verilog/axi/axi_controller.h',
                'writer/verilog/axi/axi_port.cpp',
                'writer/verilog/axi/axi_port.h',
                'writer/verilog/axi/axi_shell.cpp',
                'writer/verilog/axi/axi_shell.h',
                'writer/verilog/axi/channel_generator.cpp',
                'writer/verilog/axi/channel_generator.h',
                'writer/verilog/axi/master_controller.cpp',
                'writer/verilog/axi/master_controller.h',
                'writer/verilog/axi/master_port.cpp',
                'writer/verilog/axi/master_port.h',
                'writer/verilog/axi/slave_controller.cpp',
                'writer/verilog/axi/slave_controller.h',
                'writer/verilog/axi/slave_port.cpp',
                'writer/verilog/axi/slave_port.h',
                'writer/verilog/common.h',
                'writer/verilog/dataflow_in.cpp',
                'writer/verilog/dataflow_in.h',
                'writer/verilog/dataflow_state.cpp',
                'writer/verilog/dataflow_state.h',
                'writer/verilog/dataflow_table.cpp',
                'writer/verilog/dataflow_table.h',
                'writer/verilog/debug_marker.cpp',
                'writer/verilog/debug_marker.h',
                'writer/verilog/debug_resource.cpp',
                'writer/verilog/debug_resource.h',
                'writer/verilog/embedded_modules.cpp',
                'writer/verilog/embedded_modules.h',
                'writer/verilog/ext_combinational.cpp',
                'writer/verilog/ext_combinational.h',
                'writer/verilog/ext_io.cpp',
                'writer/verilog/ext_io.h',
                'writer/verilog/ext_io_accessor.cpp',
                'writer/verilog/ext_io_accessor.h',
                'writer/verilog/ext_task_call.cpp',
                'writer/verilog/ext_task_call.h',
                'writer/verilog/ext_task.cpp',
                'writer/verilog/ext_task.h',
                'writer/verilog/fifo.cpp',
                'writer/verilog/fifo.h',
                'writer/verilog/fifo_accessor.cpp',
                'writer/verilog/fifo_accessor.h',
                'writer/verilog/indent.cpp',
                'writer/verilog/indent.h',
                'writer/verilog/insn_writer.cpp',
                'writer/verilog/insn_writer.h',
                'writer/verilog/internal_sram.cpp',
                'writer/verilog/internal_sram.h',
                'writer/verilog/module.cpp',
                'writer/verilog/module.h',
                'writer/verilog/operator.cpp',
                'writer/verilog/operator.h',
                'writer/verilog/port.cpp',
                'writer/verilog/port.h',
                'writer/verilog/port_set.cpp',
                'writer/verilog/port_set.h',
                'writer/verilog/resource.cpp',
                'writer/verilog/resource.h',
                'writer/verilog/self_shell.cpp',
                'writer/verilog/self_shell.h',
                'writer/verilog/shared_memory.cpp',
                'writer/verilog/shared_memory.h',
                'writer/verilog/shared_memory_accessor.cpp',
                'writer/verilog/shared_memory_accessor.h',
                'writer/verilog/shared_memory_replica.cpp',
                'writer/verilog/shared_memory_replica.h',
                'writer/verilog/shared_reg_accessor.cpp',
                'writer/verilog/shared_reg_accessor.h',
                'writer/verilog/shared_reg_ext_writer.cpp',
                'writer/verilog/shared_reg_ext_writer.h',
                'writer/verilog/shared_reg.cpp',
                'writer/verilog/shared_reg.h',
                'writer/verilog/sram_if.cpp',
                'writer/verilog/sram_if.h',
                'writer/verilog/state.cpp',
                'writer/verilog/state.h',
                'writer/verilog/study.cpp',
                'writer/verilog/study.h',
                'writer/verilog/study_accessor.cpp',
                'writer/verilog/study_accessor.h',
                'writer/verilog/table.cpp',
                'writer/verilog/table.h',
                'writer/verilog/task.cpp',
                'writer/verilog/task.h',
                'writer/verilog/task_call.cpp',
                'writer/verilog/task_call.h',
                'writer/verilog/ticker.cpp',
                'writer/verilog/ticker.h',
                'writer/verilog/ticker_accessor.cpp',
                'writer/verilog/ticker_accessor.h',
                'writer/verilog/verilog_writer.cpp',
                'writer/verilog/verilog_writer.h',
                'writer/verilog/wire/accessor_info.cpp',
                'writer/verilog/wire/accessor_info.h',
                'writer/verilog/wire/distance_regs.cpp',
                'writer/verilog/wire/distance_regs.h',
                'writer/verilog/wire/inter_module_wire.cpp',
                'writer/verilog/wire/inter_module_wire.h',
                'writer/verilog/wire/mux.cpp',
                'writer/verilog/wire/mux.h',
                'writer/verilog/wire/mux_node.cpp',
                'writer/verilog/wire/mux_node.h',
                'writer/verilog/wire/names.cpp',
                'writer/verilog/wire/names.h',
                'writer/verilog/wire/wire_set.cpp',
                'writer/verilog/wire/wire_set.h',
            ],
            'dependencies': [
            ],
        },
        {
            'target_name': 'base',
            'product_name': 'base',
            'type': 'static_library',
            'include_dirs': [
                './',
            ],
            'sources': [
                'iroha/base/file.cpp',
                'iroha/base/file.h',
                'iroha/base/util.cpp',
                'iroha/base/util.h',
            ],
        },
    ]
}
