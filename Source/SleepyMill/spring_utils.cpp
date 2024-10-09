#include "spring_utils.h"

namespace spring_utils
{
	void calc_damped_spring_motion_params(damped_spring_params_t& spring_param, float dt, float angular_frequency, float damping_ratio)
	{
		float epsilon = 0.0001;

		if (damping_ratio < 0.0)
			damping_ratio = 0.0;
		if (angular_frequency < 0.0)
			angular_frequency = 0.0;

		if (angular_frequency < epsilon)
		{
			spring_param.m_pos_pos_coef = 1.0;
			spring_param.m_pos_vel_coef = 0.0;
			spring_param.m_vel_pos_coef = 0.0;
			spring_param.m_vel_vel_coef = 1.0;
			return;			
		}

		if (damping_ratio > 1.0 + epsilon)
		{
			float za = -angular_frequency * damping_ratio;
			float zb = angular_frequency * sqrt(damping_ratio * damping_ratio - 1.0);
			float z1 = za - zb;
			float z2 = za + zb;

			float e1 = exp(z1 * dt);
			float e2 = exp(z2 * dt);

			float invTwoZb = 1.0 / (2.0 * zb);

			float e1_Over_TwoZb = e1 * invTwoZb;
			float e2_Over_TwoZb = e2 * invTwoZb;

			float z1e1_Over_TwoZb = z1 * e1_Over_TwoZb;
			float z2e2_Over_TwoZb = z2 * e2_Over_TwoZb;

			spring_param.m_pos_pos_coef = e1_Over_TwoZb * z2 - z2e2_Over_TwoZb + e2;
			spring_param.m_pos_vel_coef = -e1_Over_TwoZb + e2_Over_TwoZb;

			spring_param.m_vel_pos_coef = (z1e1_Over_TwoZb - z2e2_Over_TwoZb + e2) * z2;
			spring_param.m_vel_vel_coef = -z1e1_Over_TwoZb + z2e2_Over_TwoZb;
		}
		else
		{
			
			if (damping_ratio < 1.0 - epsilon)
			{
				float omegaZeta = angular_frequency * damping_ratio;
				float alpha = angular_frequency * sqrt(1.0 - damping_ratio * damping_ratio);

				float expTerm = exp(-omegaZeta * dt);
				float cosTerm = cos(alpha * dt);
				float sinTerm = sin(alpha * dt);

				float invAlpha = 1.0 / alpha;

				float expSin = expTerm * sinTerm;
				float expCos = expTerm * cosTerm;
				float expOmegaZetaSin_Over_Alpha = expTerm * omegaZeta * sinTerm * invAlpha;

				spring_param.m_pos_pos_coef = expCos + expOmegaZetaSin_Over_Alpha;
				spring_param.m_pos_vel_coef = expSin * invAlpha;

				spring_param.m_vel_pos_coef = -expSin * alpha - omegaZeta * expOmegaZetaSin_Over_Alpha;
				spring_param.m_vel_vel_coef = expCos - expOmegaZetaSin_Over_Alpha;
			}
			else
			{
				float expTerm = exp(-angular_frequency * dt);
				float timeExp = dt * expTerm;
				float timeExpFreq = timeExp * angular_frequency;

				spring_param.m_pos_pos_coef = timeExpFreq + expTerm;
				spring_param.m_pos_vel_coef = timeExp;

				spring_param.m_vel_pos_coef = -angular_frequency * timeExpFreq;
				spring_param.m_vel_vel_coef = -timeExpFreq + expTerm;				
			}			
		}
	}

	void compute_spring_goal_vector(FVector2d desired_goal, damped_spring_vector_2d_t& spring_data, damped_spring_params_t& spring_param)
	{
		FVector2d equilibriumPos = desired_goal;

		FVector2d oldPos = spring_data.current_position - equilibriumPos;
		FVector2d oldVel = spring_data.current_velocity;

		spring_data.current_position = oldPos * spring_param.m_pos_pos_coef + oldVel * spring_param.m_pos_vel_coef + equilibriumPos;
		spring_data.current_velocity = oldPos * spring_param.m_vel_pos_coef + oldVel * spring_param.m_vel_vel_coef;
	}

	void compute_spring_goal_vector(FVector desired_goal, damped_spring_vector_t& spring_data, damped_spring_params_t& spring_param)
	{
		FVector equilibriumPos = desired_goal;

		FVector oldPos = spring_data.current_position - equilibriumPos;
		FVector oldVel = spring_data.current_velocity;

		spring_data.current_position = oldPos * spring_param.m_pos_pos_coef + oldVel * spring_param.m_pos_vel_coef + equilibriumPos;
		spring_data.current_velocity = oldPos * spring_param.m_vel_pos_coef + oldVel * spring_param.m_vel_vel_coef;
	}

	void compute_spring_goal_float(float desired_goal, damped_spring_float_t& spring_data, damped_spring_params_t& spring_param)
	{
		float equilibriumPos = desired_goal;

		float oldPos = spring_data.current_position - equilibriumPos;
		float oldVel = spring_data.current_velocity;

		spring_data.current_position = oldPos * spring_param.m_pos_pos_coef + oldVel * spring_param.m_pos_vel_coef + equilibriumPos;
		spring_data.current_velocity = oldPos * spring_param.m_vel_pos_coef + oldVel * spring_param.m_vel_vel_coef;		
	}
}
