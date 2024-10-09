#pragma once

namespace spring_utils
{
	struct damped_spring_params_t
	{
		float m_pos_pos_coef = 0.0;
		float m_pos_vel_coef = 0.0;
		float m_vel_pos_coef = 0.0;
		float m_vel_vel_coef = 0.0;
	};

	struct damped_spring_vector_2d_t
	{
		FVector2d current_position;
		FVector2d current_velocity;
	};
	
	struct damped_spring_vector_t
	{
		FVector current_position;
		FVector current_velocity;
	};
	
	struct damped_spring_float_t
	{
		float current_position;
		float current_velocity;
	};
	
	void calc_damped_spring_motion_params(damped_spring_params_t& spring_param, float dt, float angular_frequency, float damping_ratio);
	void compute_spring_goal_vector(FVector2d desired_goal, damped_spring_vector_2d_t& spring_data, damped_spring_params_t& spring_param);
	void compute_spring_goal_vector(FVector desired_goal, damped_spring_vector_t& spring_data, damped_spring_params_t& spring_param);
	void compute_spring_goal_float(float desired_goal, damped_spring_float_t& spring_data, damped_spring_params_t& spring_param);
}