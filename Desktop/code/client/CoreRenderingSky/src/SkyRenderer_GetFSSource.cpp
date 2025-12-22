/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "SkyRenderer.hpp"

namespace Forradia
{
    auto SkyRenderer::GetFSSource() const -> std::string
    {
        return R"(
            #version 330 core
            
            #define PI 3.14159265359
            
            out vec4 FragColor;
                
            in vec3 viewDirection;

            uniform vec3 sunDirection;
            uniform float sunElevation;

            void main()
            {
                // viewDirection is the normalized direction from center to vertex.
                // This represents the view direction for sky color calculation.

                vec3 viewDir = normalize(viewDirection);
                
                // Calculate the elevation angle of the view direction (0 = horizon, PI/2 = zenith).
                // viewDir.z ranges from 0.0 (horizon) to 1.0 (zenith) since +Z is up.
                // Elevation angle from horizon = asin(viewDir.z)

                float viewElevation = asin(clamp(viewDir.z, 0.0, 1.0));
                
                // Calculate the angle between the view direction and sun direction.

                float sunDot = dot(viewDir, sunDirection);
                float sunAngle = acos(clamp(sunDot, -1.0, 1.0));
                
                // Base sky colors for day time.

                vec3 horizonColor = vec3(0.0, 0.5, 1.0);  // Light blue at horizon.
                vec3 zenithColor = vec3(0.1, 0.1, 0.2);   // Darker blue at zenith.
                vec3 sunColor = vec3(1.0, 0.9, 0.7);      // Warm sun color.
                
                // Adjust colors based on sun elevation.

                // Clamp sun elevation to reasonable range and calculate sun factor.
                float clampedSunElevation = clamp(sunElevation, -PI / 2.0, PI / 2.0);
                float sunFactor = max(0.0, sin(clampedSunElevation));
                
                // Darker sky when sun is below horizon (night) or very low.

                if (clampedSunElevation < 0.1)
                {
                    // Interpolate between day and night colors based on sun elevation.
                    float nightFactor = 1.0 - clamp((clampedSunElevation + PI / 2.0) / (PI / 2.0 + 0.1), 0.0, 1.0);
                    horizonColor = mix(vec3(0.5, 0.7, 1.0), vec3(0.05, 0.05, 0.15), nightFactor);
                    zenithColor = mix(vec3(0.3, 0.5, 0.9), vec3(0.0, 0.0, 0.1), nightFactor);
                    if (clampedSunElevation < 0.0)
                    {
                        sunFactor = 0.0;
                    }
                }
                
                // Interpolate between horizon and zenith colors based on view elevation.

                float elevationFactor = viewElevation / (PI / 2.0);
                vec3 skyColor = mix(horizonColor, zenithColor, elevationFactor);
                
                // Add sun glow around the sun position.

                float sunGlow = 0.0;
                if (sunAngle < 0.3)  // Within ~17 degrees of sun.
                {
                    sunGlow = (1.0 - sunAngle / 0.3) * sunFactor * 0.5;
                    skyColor = mix(skyColor, sunColor, sunGlow);
                }
                
                // Add atmospheric scattering effect (reddish glow near horizon when sun is low).
                
                if (viewElevation > 2.0 && clampedSunElevation > 0.0 && clampedSunElevation < 0.5)
                {
                    float horizonGlow = (viewElevation - 2.0) / (PI - 2.0);
                    horizonGlow = clamp(horizonGlow, 0.0, 1.0);
                    vec3 sunsetColor = vec3(1.0, 0.6, 0.3);
                    skyColor = mix(skyColor, sunsetColor, horizonGlow * (1.0 - clampedSunElevation / 0.5) * 0.3);
                }
                
                FragColor = vec4(skyColor, 1.0);
            }
        )";
    }
}
