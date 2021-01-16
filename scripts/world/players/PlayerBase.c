modded class PlayerBase
{
    const int RPC_TOGGLE_LSD_LIGHT = 42069;
    const int RPC_TOGGLE_MILKTRIP = 69069;
    const int RPC_TOGGLE_SHROOMTRIP = 69169;
    ScriptedLightBase buzz;
    void createlight()
    {
        //check if client-side
            if (GetGame().IsClient() || !GetGame().IsMultiplayer()) 
        {
            // Create light
            buzz = ScriptedLightBase.CreateLight(TrippingLights);
            // Attach to player
            buzz.AttachOnObject(this);
        }
    }
    
    void toggle_light(bool state)
    {  
        if (state) {
            createlight();
        } else{
            buzz.Destroy();
        }
    }
    void milk_trip(bool state)
    {  
        if (state) {
            PPEffects.FlashbangEffect(0.3);
		    PPEffects.SetBlurFlashbang(0.3);
		    PPEffects.UpdateColor();
        } else{
            PPEffects.FlashbangEffect(0);
		    PPEffects.UpdateColor();
		    PPEffects.SetBlurFlashbang(0);        
        }
    }

    void shroom_trip(bool state)
    {  
        if (state) {

            PPEffects.SetEVValuePP(-3);
			PPEffects.SetColorizationNV(1.0, 0, 1.0);
			PPEffects.SetNVParams(100.0, 2.0, 9.0, 1.0);

            //static void SetNVParams(float light_mult, float noise_intensity, float sharpness, float grain_size)
        } else{
            PPEffects.SetEVValuePP(0);
			PPEffects.SetColorizationNV(1.0, 1.0, 1.0);
			PPEffects.SetNVParams(1.0, 0.0, 2.35, 2.75); //default values        
        }
    }


    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);        
        switch (rpc_type) {
            case RPC_TOGGLE_LSD_LIGHT: {
                Param1<bool> tripping_params;
                if (!ctx.Read(tripping_params)) {
                    break;
                }
                
                toggle_light(tripping_params.param1);
                break;
            }
            case RPC_TOGGLE_MILKTRIP: {
                Param1<bool> milktrip_params;
                if (!ctx.Read(milktrip_params)) {
                    break;
                }
                
                milk_trip(milktrip_params.param1);
                break;
            }
            case RPC_TOGGLE_SHROOMTRIP: {
                Param1<bool> shroomtrip_params;
                if (!ctx.Read(shroomtrip_params)) {
                    break;
                }
                
                shroom_trip(shroomtrip_params.param1);
                break;
            }
        }
    }
}