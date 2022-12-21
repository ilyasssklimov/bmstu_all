import PreviewModel from "../models/PostModel";

class GuestService {
    baseAddress = "http://localhost:8001/api/v1/"

    getResource = async (url: string) => {
        let result = await fetch(this.baseAddress + url);
    
        if (!result.ok) {
            throw new Error(`Error while fetching ${url}, status: ${result.status}`);
        }
    
        return await result.json();
    }

    getPreviews = async () => {
        let previewsJson = await this.getResource("previews")
        let previews = [] as PreviewModel[]
        
        previewsJson["previews"].forEach((preview: PreviewModel) => {
            previews.push(Object.assign(new PreviewModel(), preview))
        });
        
        return previews
    }
}

export default GuestService