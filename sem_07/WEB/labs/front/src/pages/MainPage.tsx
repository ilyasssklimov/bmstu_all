import Post from "../components/post/Post"
import GuestService from "../services/GuestService"
import PreviewModel from "../models/PostModel"


const MainPage = () => {
    let guestService = new GuestService()
    let previewsArray = guestService.getPreviews()

    function renderPreviews(previewsArray: Promise<PreviewModel[]>) {
        let fromIndex = 0
        let toIndex = 9
        const previews = previewsArray.slice(fromIndex, toIndex).map((preview, i) => {
            return (
                <td key={i}>
                    <Post 
                    name={preview.name} 
                    author={preview.author.login} 
                    city={preview.city} 
                    date={preview.date}
                    information={preview.information}
                    />
                </td>
            )
        })

        return (
            {previews}
        )
    }

    const previews = renderPreviews(previewsArray)

    return (
        <div className="main_page">
            <table width="100%">
                <tr>
                    
                </tr>
            </table>
        </div>
    )
}

export default MainPage;