#include "./gDiffFramework.h"

GLayerCfg* newGLayerCfg(){

    GLayerCfg* newLayer = (GLayerCfg*) malloc(sizeof(GLayerCfg));

    if(newLayer != NULL){

        newLayer->layerBuffer = NULL;
        newLayer->shadeProgram = NULL;
        /**newLayer->layerBuffer = newGBuffer();

        if(newLayer->layerBuffer == NULL){
            free(newLayer);
            return NULL;
        }

        newLayer->shadeProgram = newGShader();
        if(newLayer->shadeProgram == NULL){
            deleteGBuffer(&(newLayer->layerBuffer));
            free(newLayer);
            return NULL;
        }*/
    }

    return newLayer;

}

GLayerCfg* wrapGLayerCfg(int(*paintRoutine)(GLayerCfg*, void*),
                            GBuffer* newLayerBuff,
                            GShader* newProgram){

    GLayerCfg* newLayer = (GLayerCfg*) malloc(sizeof(GLayerCfg));

    if(newLayer != NULL){

        newLayer->layerBuffer = newLayerBuff;
        newLayer->paint = paintRoutine;
        newLayer->shadeProgram = newProgram;

    }

    return newLayer;

}

int deleteGLayerCfg(GLayerCfg** self){

    /**This is a fairly naive deletion routine; DON'T TRUST IT.*/
    free(*self);
    *self = NULL;

    return 0;

}

GRenderCfg* newGRenderCfg(size_t nBuffs){

    //Iterator variable for looping over GBufferCfg allocation
    size_t i = 0;

    // The pointer to the new RenderCfg
    GRenderCfg* newRenderCfg = (GRenderCfg*)malloc(sizeof (GRenderCfg));

    //Allocate and assign GBufferCfg's

    // Allocate the array of GBufferCfg pointers, but only if
    // we have at least one buffer to allocate
    GLayerCfg** buffers = NULL;

    if(nBuffs != 0){
        buffers = (GLayerCfg**) malloc((sizeof (GLayerCfg*)) * nBuffs);
    }

    //Fill the array with new GBufferCfg's
    for(i=0; i < nBuffs; i++){
        //Technically, incrementing the pointer would be faster, but
        // we don't expect to be allocating many RenderCfg's
        buffers[i] = NULL;
    }

    // This will be set to NULL if you didn't ask for any buffers
    newRenderCfg->bufferCfgs = buffers;

    newRenderCfg->nBuffers = nBuffs;

    return newRenderCfg;

}

GRenderCfg* makeGRenderCfg(size_t nBuffs,
                           int(*renderRoutine)(GRenderCfg*, void*)){

    //Iterator variable for looping over GBufferCfg allocation
    size_t i = 0;

    // The pointer to the new RenderCfg
    GRenderCfg* newRenderCfg = (GRenderCfg*)malloc(sizeof (GRenderCfg));

    if(newRenderCfg != NULL){

        newRenderCfg->render = renderRoutine;

        //Allocate and assign GBufferCfg's

        // Allocate the array of GBufferCfg pointers, but only if
        // we have at least one buffer to allocate
        GLayerCfg** buffers = NULL;

        if(nBuffs != 0){
            buffers = (GLayerCfg**) malloc((sizeof (GLayerCfg*)) * nBuffs);
        }

        //Fill the array with new GBufferCfg's
        for(i=0; i < nBuffs; i++){
            //Technically, incrementing the pointer would be faster, but
            // we don't expect to be allocating many RenderCfg's
            buffers[i] = NULL;
        }

        // This will be set to NULL if you didn't ask for any buffers
        newRenderCfg->bufferCfgs = buffers;

        newRenderCfg->nBuffers = nBuffs;

    }

    return newRenderCfg;

}

int setBufferN(GRenderCfg* aRenderCfg, size_t buffer, GLayerCfg* aBuff){

    if(aRenderCfg != NULL){
        if( aBuff != NULL){
            if( buffer > 0){
                if( buffer <= aRenderCfg->nBuffers){
                    aRenderCfg->bufferCfgs[buffer-1] = aBuff;
                    return G_SUCCESS;
                } else {
                    return G_INDEX_OUT_OF_BOUNDS;
                }
            } else {
                return G_INDEX_NEGATIVE;
            }
        } else {
            return G_ID_ZERO;
        }
    }
    return G_SELF_NULL;
}

int deleteGRenderCfg(GRenderCfg** aRenderCfg){

    // Iterator variable
    size_t i = 0;

    //Current Buffer to delete

    for( i=0; i < (*aRenderCfg)->nBuffers; i++){
        deleteGLayerCfg(&(*aRenderCfg)->bufferCfgs[i]);
    }

    free((*aRenderCfg)->bufferCfgs);
    free(*aRenderCfg);
    *aRenderCfg = NULL;

    return 0;

}
