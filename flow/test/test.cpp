
#include "stdafx.h"

// intentionally include cpp files -- boost.test takes a million years to compile

// core
#include "general.cpp"
#include "iterator.cpp"
#include "lazy.cpp"
#include "optional_reference.cpp"
#include "optional_value.cpp"
#include "uncurry.cpp"

// generator
#include "closed_range_inc.cpp"
#include "closed_range_op.cpp"

#include "cycle_container.cpp"
#include "cycle_container_n.cpp"
#include "cycle_itr.cpp"
#include "cycle_itr_n.cpp"
#include "cycle_list.cpp"
#include "cycle_list_n.cpp"
#include "cycle_move_container.cpp"
#include "cycle_move_container_n.cpp"
#include "rcycle_container.cpp"
#include "rcycle_container_n.cpp"
#include "rcycle_move_container.cpp"
#include "rcycle_move_container_n.cpp"

#include "empty_t.cpp"

#include "from_container.cpp"
#include "from_itr.cpp"
#include "from_list.cpp"
#include "from_move_container.cpp"
#include "rfrom_container.cpp"
#include "rfrom_move_container.cpp"

#include "generate_func.cpp"
#include "generate_func_n.cpp"

#include "iota_inc.cpp"
#include "iota_op.cpp"

#include "iterate_func.cpp"

#include "rand_bools.cpp"
#include "rand_distrib.cpp"
#include "rand_engine.cpp"
#include "rand_ints.cpp"
#include "rand_reals.cpp"

#include "range_inc.cpp"
#include "range_op.cpp"

#include "repeat_n.cpp"
#include "repeat_val.cpp"

// intermediate
#include "concat_container.cpp"
#include "concat_itr.cpp"
#include "concat_list.cpp"
#include "concat_stream.cpp"

#include "drop_while_bool.cpp"
#include "drop_while_func.cpp"
#include "drop_while_member.cpp"
#include "drop_while_member_const.cpp"

#include "filter_bool.cpp"
#include "filter_func.cpp"
#include "filter_member.cpp"
#include "filter_member_const.cpp"

#include "flat_map_t.cpp"

#include "limit_t.cpp"

#include "map_func.cpp"
#include "map_member.cpp"
#include "map_member_const.cpp"

#include "merge_container_comp.cpp"
#include "merge_container_less.cpp"
#include "merge_itr_comp.cpp"
#include "merge_itr_less.cpp"
#include "merge_list_comp.cpp"
#include "merge_list_less.cpp"
#include "merge_stream_comp.cpp"
#include "merge_stream_less.cpp"

#include "peek_func.cpp"
#include "peek_member.cpp"
#include "peek_member_const.cpp"

#include "replace_if_t.cpp"
#include "replace_map_t.cpp"
#include "replace_val.cpp"

#include "reverse_t.cpp"

#include "set_diff_container_comp.cpp"
#include "set_diff_container_less.cpp"
#include "set_diff_itr_comp.cpp"
#include "set_diff_itr_less.cpp"
#include "set_diff_list_comp.cpp"
#include "set_diff_list_less.cpp"
#include "set_diff_stream_comp.cpp"
#include "set_diff_stream_less.cpp"

#include "set_intersect_container_comp.cpp"
#include "set_intersect_container_less.cpp"
#include "set_intersect_itr_comp.cpp"
#include "set_intersect_itr_less.cpp"
#include "set_intersect_list_comp.cpp"
#include "set_intersect_list_less.cpp"
#include "set_intersect_stream_comp.cpp"
#include "set_intersect_stream_less.cpp"

#include "set_sym_diff_container_comp.cpp"
#include "set_sym_diff_container_less.cpp"
#include "set_sym_diff_itr_comp.cpp"
#include "set_sym_diff_itr_less.cpp"
#include "set_sym_diff_list_comp.cpp"
#include "set_sym_diff_list_less.cpp"
#include "set_sym_diff_stream_comp.cpp"
#include "set_sym_diff_stream_less.cpp"

#include "set_union_container_comp.cpp"
#include "set_union_container_less.cpp"
#include "set_union_itr_comp.cpp"
#include "set_union_itr_less.cpp"
#include "set_union_list_comp.cpp"
#include "set_union_list_less.cpp"
#include "set_union_stream_comp.cpp"
#include "set_union_stream_less.cpp"

#include "shuffle_t.cpp"

#include "skip_every_t.cpp"
#include "skip_op.cpp"
#include "skip_step.cpp"

#include "slice_op.cpp"
#include "slice_step.cpp"

#include "sort_comp.cpp"
#include "sort_less.cpp"
#include "stable_sort_comp.cpp"
#include "stable_sort_less.cpp"

#include "take_while_bool.cpp"
#include "take_while_func.cpp"
#include "take_while_member.cpp"
#include "take_while_member_const.cpp"

#include "unique_comp.cpp"
#include "unique_less.cpp"

#include "zip_container_default.cpp"
#include "zip_container_func.cpp"
#include "zip_itr_default.cpp"
#include "zip_itr_func.cpp"
#include "zip_list_default.cpp"
#include "zip_list_func.cpp"
#include "zip_stream_default.cpp"
#include "zip_stream_func.cpp"

// terminal
#include "all_bool.cpp"
#include "all_func.cpp"
#include "all_member.cpp"
#include "all_member_const.cpp"

#include "any_bool.cpp"
#include "any_func.cpp"
#include "any_member.cpp"
#include "any_member_const.cpp"

#include "contains_t.cpp"

#include "copy_t.cpp"

#include "count_if_t.cpp"
#include "count_t.cpp"
#include "count_val.cpp"

#include "dump_t.cpp"

#include "each_func.cpp"
#include "each_member.cpp"
#include "each_member_const.cpp"

#include "execute_t.cpp"

#include "first_t.cpp"

#include "fold_id_init.cpp"
#include "fold_id_opt.cpp"
#include "fold_init.cpp"
#include "fold_opt.cpp"

#include "inner_product_t.cpp"

#include "last_t.cpp"

#include "max_comp.cpp"
#include "max_less.cpp"
#include "min_comp.cpp"
#include "min_less.cpp"
#include "minmax_comp.cpp"
#include "minmax_less.cpp"

#include "none_bool.cpp"
#include "none_func.cpp"
#include "none_member.cpp"
#include "none_member_const.cpp"

#include "nth_t.cpp"

#include "product_init.cpp"
#include "product_opt.cpp"

#include "reservoir_t.cpp"
#include "sample_heap_t.cpp"
#include "sample_shuffle_t.cpp"
#include "sample_t.cpp"

#include "stats_t.cpp"

#include "sum_init.cpp"
#include "sum_opt.cpp"

#include "to_deque_t.cpp"
#include "to_forward_list_t.cpp"
#include "to_group_t.cpp"
#include "to_list_t.cpp"
#include "to_map_t.cpp"
#include "to_multiset_t.cpp"
#include "to_set_t.cpp"
#include "to_unordered_map_t.cpp"
#include "to_unordered_multiset_t.cpp"
#include "to_unordered_set_t.cpp"
#include "to_vector_t.cpp"
