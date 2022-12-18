import "./Post.css"
import OpenButton from "../openButton/OpenButton";


const Post = ({ name, author, city, date, information }: 
    { name: string, author: string, city: string, date: string, information: string}) => {

        let infoLength = 220;
        return (
            <div className="post">
                <text className="name">{ name }</text>
                <div className="data">
                    <p>Автор: { author }</p>
                    <p>Город: { city }</p>
                    <p>Дата: { date }</p>
                    <p>Информация:</p><p>{ information.slice(0, infoLength) + "..." }</p>
                </div>
                <OpenButton/>
            </div>
        )
}

export default Post;